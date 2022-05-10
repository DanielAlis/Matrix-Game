//
// Created by Alis Daniel on 19/06/2021.
//


#include "Game.h"


Game::Game(int height, int width) {
    if (width <= 0|| height <= 0)
    {
        throw mtm::IllegalArgument();
    }
    this->board = new mtm::GameBoard<std::shared_ptr<Character>>(height,width, nullptr);
}

Game::Game(const Game& other) {
    this->board = new mtm::GameBoard<std::shared_ptr<Character>>(other.board->getRow(),
                                                        other.board->getColumn(), nullptr);
    for(int i=0; i < this->board->getRow(); i++) {
        for (int j = 0; j < this->board->getColumn(); j++) {
            if ((*other.board)(i, j) != nullptr) {
                (*this->board)(i, j) = std::shared_ptr<Character>((*other.board)(i, j)->clone());
            }
        }
    }
}

Game& Game::operator=(const Game &other) {
    if (this == &other) {
        return *this;
    }

    delete this->board;
    this->board = new mtm::GameBoard<std::shared_ptr<Character>>(other.board->getRow(),
                                                    other.board->getColumn(), nullptr);
    for(int i=0; i < this->board->getRow(); i++)
    {
        for(int j=0; j < this->board->getColumn(); j++)
        {
            if((*other.board)(i,j) != nullptr)
            {
                (*this->board)(i,j) = std::shared_ptr<Character>((*other.board)(i,j)->clone());
            }
        }
    }
    return *this;
}

Game::~Game()
{
    if(this->board != nullptr)
    {
        delete this->board;
    }
}

void Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character)
{
    this->areCoordinatesLegal(coordinates);
    if(isOccupied(coordinates)==true)
    {
        throw mtm::CellOccupied();
    }
    (*this->board)(coordinates.row, coordinates.col) = character;
}

std::shared_ptr<Character>
Game::makeCharacter(mtm::CharacterType type, mtm::Team team, mtm::units_t health, mtm::units_t ammo,
                    mtm::units_t range, mtm::units_t power){
    if(type == mtm::SOLDIER)
    {
        std::shared_ptr<Soldier> solider_ptr(new Soldier(team, health, ammo, range, power));
        return solider_ptr;
    }
    if(type == mtm::SNIPER)
    {
        std::shared_ptr<Sniper> sniper_ptr(new Sniper(team,health,ammo,range,power));
        return sniper_ptr;
    }
    std::shared_ptr<Medic> medic_ptr(new Medic(team,health,ammo,range,power));
    return medic_ptr;
}

void Game::move(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates)
{
    areCoordinatesLegal(src_coordinates);
    areCoordinatesLegal(dst_coordinates);
    if(isOccupied(src_coordinates)==false)
    {
        throw mtm::CellEmpty();
    }
    std::shared_ptr<Character> move_character((*this->board)(src_coordinates.row, src_coordinates.col));
    int step_to_move = mtm::GridPoint::distance(src_coordinates,dst_coordinates);
    move_character.get()->isMovementLegal(step_to_move);
    addCharacter(dst_coordinates, move_character);
    (*this->board)(src_coordinates.row, src_coordinates.col) = nullptr;
}

void Game::attack(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates)
{
    areCoordinatesLegal(src_coordinates);
    areCoordinatesLegal(dst_coordinates);
    if(isOccupied(src_coordinates)==false)
    {
        throw mtm::CellEmpty();
    }
    int damage_distance = mtm::GridPoint::distance(src_coordinates, dst_coordinates);
    char type = (*this->board)(src_coordinates.row,src_coordinates.col)->getTypeOfCharacter();
    strike(damage_distance, src_coordinates, dst_coordinates, dst_coordinates, type);
    if(type == 'S' || type == 's') {
        for (int i = 0; i < this->board->getRow(); i++) {
            for (int j = 0; j < this->board->getColumn(); j++) {
                if (i != dst_coordinates.row || j != dst_coordinates.col) {
                    mtm::GridPoint attacked_location(i, j);
                    int distance = mtm::GridPoint::distance(attacked_location, src_coordinates);
                    try {
                        strike(distance, src_coordinates, dst_coordinates, attacked_location, type);
                    }
                    catch (const mtm::OutOfRange &e) {
                        if (i == dst_coordinates.row && j == dst_coordinates.col) {
                            throw mtm::OutOfRange();
                        }
                    }
                }
            }
        }
    }
}

void Game::reload(const mtm::GridPoint& coordinates)
{
    areCoordinatesLegal(coordinates);
    if(isOccupied(coordinates)==false)
    {
        throw mtm::CellEmpty();
    }
    (*this->board)(coordinates.row, coordinates.col).get()->load();
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    std::string str;
    for(int i=0; i < game.board->getRow(); i++)
    {
        for(int j=0; j < game.board->getColumn(); j++)
        {

            if((*game.board)(i,j).get() == nullptr)
            {
                str += ' ';
            }
            else
            {
                str += (*game.board)(i,j).get()->getTypeOfCharacter();
            }
        }
    }
    return mtm::printGameBoard(os, &str[0] ,&str[str.length()], game.board->getColumn());
}

bool Game::isOver(mtm::Team* winningTeam) const
{
    int counter_powerlifters = 0;
    int counter_crossfitters = 0;
    for (int i = 0 ; i < this->board->getRow(); i++)
    {
        for(int j = 0 ; j < this->board->getColumn(); j++)
        {
            std::shared_ptr<Character> check_winner_team = (*this->board)(i,j);
            updateScore(check_winner_team, &counter_powerlifters, &counter_crossfitters);
        }
    }
    if (counter_crossfitters == 0 && counter_powerlifters > 0)
    {
        updateWinningTeam(winningTeam, mtm::POWERLIFTERS);
        return true;
    }
    if (counter_crossfitters > 0 && counter_powerlifters == 0)
    {
        updateWinningTeam(winningTeam, mtm::CROSSFITTERS);
        return true;
    }
    return false;
}

void Game::areCoordinatesLegal(const mtm::GridPoint& coordinates)
{
    if (coordinates.col < 0 || coordinates.row < 0 ||
        coordinates.col >= this->board->getColumn() || coordinates.row >= this->board->getRow())
    {
        throw mtm::IllegalCell();
    }

}

bool Game::isOccupied(const mtm::GridPoint& coordinates)
{
    return (*this->board)(coordinates.row, coordinates.col) != nullptr;
}

void Game::strike(const int damage_distance, const mtm::GridPoint &src_coordinates,
        const mtm::GridPoint &dst_coordinates,const mtm::GridPoint &attacked_location, char type)
{
    bool is_enemy = false;
    bool is_empty = false;
    if(isOccupied(attacked_location) == true)
    {
        is_enemy = (*this->board)(attacked_location.row,attacked_location.col)->getTeam()
                   != (*this->board)(src_coordinates.row,src_coordinates.col)->getTeam();
    }
    else
    {
        is_empty = true;
    }
    int damage = (*this->board)(src_coordinates.row,src_coordinates.col)->characterAttack(is_empty,damage_distance,
                                                is_enemy, src_coordinates, dst_coordinates, attacked_location);
    if(isOccupied(attacked_location)==false && type != 'S' && type != 's')
    {
        throw mtm::IllegalTarget();
    }
    if(isOccupied(attacked_location)==true) {
        int life = (*this->board)(attacked_location.row, attacked_location.col)->characterAttacked(damage);
        if (life < 1) {
            (*this->board)(attacked_location.row, attacked_location.col) = nullptr;
        }
    }
}

void updateScore(const std::shared_ptr<Character>& check_winner_team,
                     int *counter_powerlifters, int *counter_crossfitters)
{
    if(check_winner_team != nullptr)
    {
        if(check_winner_team->getTeam() == mtm::POWERLIFTERS)
        {
            (*counter_powerlifters)++;
        }
        else
        {
            (*counter_crossfitters)++;
        }
    }
}

void updateWinningTeam(mtm::Team *winner, mtm::Team team)
{
    if (winner == nullptr)
    {
        winner = &team;
    }
    else
    {
        *winner = team;
    }

}

