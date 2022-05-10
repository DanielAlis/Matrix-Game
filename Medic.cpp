//
// Created by Alis Daniel on 19/06/2021.
//

#include "Medic.h"

#define MAX_STEP 5
#define AMMO_PRICE 1
#define LOADING_AMMO 5
#define POWERLIFTERS_TYPE 'M'
#define CROSSFITTERS_TYPE 'm'


Medic::Medic(const mtm::Team team,const int health,const int ammo,const int range,const int power):
        Character(team, health, ammo, range, power, MAX_STEP, AMMO_PRICE)
{}

void Medic::load()
{
    this->ammo += LOADING_AMMO;
}

int Medic::characterAttack(bool is_empty, int distance, const bool is_enemy, const mtm::GridPoint &src,
                           const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates) {
    isTargetInRange(distance, this->range);
    if(is_enemy==true || is_empty ==true)
    {
        Character::ammoPrice(this->ammo);;
    }
    isMe(src, dst);
    if(is_enemy==true)
    {
        this->ammo -= AMMO_PRICE;
        return this->power;
    }
    return -(this->power); 
}

int Medic::characterAttacked(const int damage) {
    this->health -= damage;
    return health;
}

Character *Medic::clone() const {
    return new Medic(*this);
}

char Medic::getTypeOfCharacter() {
    if(this->team == mtm::POWERLIFTERS)
    {
        return POWERLIFTERS_TYPE;
    }
    return CROSSFITTERS_TYPE;
}

void Medic::isMe(const mtm::GridPoint &src, const mtm::GridPoint &dst)
{
    if(src.row == dst.row && src.col == dst.col)
    {
        throw mtm::IllegalTarget();
    }
}


