//
// Created by Alis Daniel on 19/06/2021.
//

#include "Soldier.h"

#define RANGE 3
#define ATTACK 2
#define MAX_STEPS 3
#define AMMO_PRICE 1
#define LOADING_AMMO 3
#define POWERLIFTERS_TYPE 'S'
#define CROSSFITTERS_TYPE 's'


Soldier::Soldier(mtm::Team team, const int health, const int ammo, const int range, const int power):
        Character(team, health, ammo, range, power, MAX_STEPS, AMMO_PRICE)
{}

void Soldier::load()
{
    this->ammo += LOADING_AMMO;
}

int Soldier::characterAttack(bool is_empty, int distance, const bool is_enemy, const mtm::GridPoint &src,
                             const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates) {
    bool main_damage = (attackers_coordinates.col == dst.col && attackers_coordinates.row == dst.row );
    if (main_damage==true) {
        isTargetInRange(distance, this->range);
        Character::ammoPrice(this->ammo);
        isLine(src, dst);
        this->ammo -= AMMO_PRICE;
        if (is_enemy==true) {
            return power;
        }
    }
    else
    {
        int max_distance = range / RANGE + (range % RANGE != 0);
        isTargetInRange(mtm::GridPoint::distance(dst, attackers_coordinates), max_distance);
        if (is_enemy==true) {
            return power / ATTACK + (power % ATTACK != 0); // Collateral damage value
        }
    }
    return 0;
}

int Soldier::characterAttacked(const int damage)
{
    this->health -= damage;
    return this->health;
}

Character *Soldier::clone() const {
    return new Soldier(*this);
}

char Soldier::getTypeOfCharacter() {
    if(this->team == mtm::POWERLIFTERS)
    {
        return POWERLIFTERS_TYPE;
    }
    return CROSSFITTERS_TYPE;
}

void Soldier::isLine(const mtm::GridPoint& src, const mtm::GridPoint& dst)
{
    if(src.col != dst.col && src.row != dst.row)
    {
        throw mtm::IllegalTarget();
    }
}


