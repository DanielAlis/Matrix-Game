//
// Created by Alis Daniel on 19/06/2021.
//

#ifndef UNTITLED6_GAME_H
#define UNTITLED6_GAME_H

#include <memory>

#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Auxiliaries.h"
#include "GameBoard.h"


class Game {
    mtm::GameBoard<std::shared_ptr<Character>> *board;

    /** areCoordinatesLegal: Checks if coordinates are legal.
     * @param coordinates- the coordinates it checks.
    */
    void areCoordinatesLegal(const mtm::GridPoint& coordinates);

    /** isOccupied: checks if the cell is occupied by a character.
     * @param coordinates- paramater used for printing out stuff.
     * 
     * @return 
     * true - the board does have a character in those coordinates.
     * false- the board doesn't have a character in those coordinates.
    */
    bool isOccupied(const mtm::GridPoint& coordinates);

    /** strike: strikes the character placed in attacked_location.
     * @param damage_distance- the distance between src and dst.
     * @param src_coordinates- the attacker's location.
     * @param dst_coordinates- the location that's being attacked.
     * @param attacked_location- the location of the enemy character.
     * @param type- the type of the attacking character.
    */
    void strike(const int damage_distance, const mtm::GridPoint& src_coordinates, 
        const mtm::GridPoint& dst_coordinates, const mtm::GridPoint& attacked_location, char type);

public:
    
    /** Constructor: creates game from height and width.
     * @param height - how high is the gameBoard.
     * @param width - how wide is the gameBoard.
    */
    Game(int height, int width);

    /** Copy constructor: creates game from given game other.
     * @param other- the game it creates a copy of .
     */
    Game(const Game& other);

    /** operator=: Returns a reference to a new game, with given game other parameters.
     * @param other- the game it copies to this.
     * 
     * @return 
     * it returns a copy of the game.
    */
    Game& operator=(const Game& other);

    // destructor: deletes the game and dellocates its memory.
    ~Game();

    /** addCharacter: adds a character of a certain type to given coordinates.
     * @param coordinates- the coordinates in which to place the character.
     * @param character- a pointer to the character.
    */
    void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);

    /** makeCharacter: Creates a new character with given parameters.
     * @param type- the type of character to create.
     * @param team- the team of the character.
     * @param health- the amount of health the chracter has.
     * @param ammo- the amount of ammo the character starts with.
     * @param range- the range of the character's attack.
     * @param power- the amount of damage per single attack the character does.
     * 
     * @return 
     * pointer to a type of character.
    */
    static std::shared_ptr<Character> makeCharacter(mtm::CharacterType type, mtm::Team team,
                                                    mtm::units_t health, mtm::units_t ammo,
                                                    mtm::units_t range, mtm::units_t power);

    /** move:  Moves character from source coordinates to destination coordinates.
     * @param src_coordinates- the place where the character starts.
     * @param dst_coordinates- the place where the character wants to go to.
    */
    void move(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);

    /** attack: attacks from the character in src to dst.
     * @param src_coordinates- the place where the character who attacks is.
     * @param dst_coordinates- the place where the character is attacking.
    */
    void attack(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);

    /** reload: Ammo reload for character in coordinates.
     * @param src_coordinates- reloads the character in that space (if there is).
    */
    void reload(const mtm::GridPoint & coordinates);

    /** isOver: Checks if the game has ended (only one team left).
     * @param winningTeam- paramater used for printing out stuff.
     * 
     * @return 
     * true - over and updates winningTeam to hold the winner.
     * false- not over.
    */
    bool isOver(mtm::Team* winningTeam=nullptr) const;


    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
/** operator<<: Adds game board values to os in order (row by row, from left to right).
 * @param os- paramater used for printing out stuff.
 * @param game- the game it wants to print onto the screen.
 * 
 * @return 
 * the state of the printing of the board.
*/
std::ostream& operator<<(std::ostream& os, const Game& game);

/** updateScore: updates the score of both team.
 * @param check_winner_team- the team who won.
 * @param counter_powerlifters- the amount of wins powerlifters have.
 * @param counter_crossfitters- the amount of wins crossfitters have.
*/
void updateScore(const std::shared_ptr<Character>& check_winner_team,
                     int *counter_powerlifters, int *counter_crossfitters);

/** updateWinningTeam: Updates pointer winner to winning team.
 * @param winner- pointer to the winning team.
 * @param team- the team who won.
*/                     
void updateWinningTeam(mtm::Team *winner, mtm::Team team);


#endif //UNTITLED6_GAME_H
