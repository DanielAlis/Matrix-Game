//
// Created by Alis Daniel on 19/06/2021.
//
#include "Sniper.h"


#define ATTACK_BONUS 2
#define TRIPLE_ATTACK 3
#define RANGE 2
#define MAX_STEPS 4
#define AMMO_PRICE 1
#define LOADING_AMMO 2
#define POWERLIFTERS_TYPE 'N'
#define CROSSFITTERS_TYPE 'n'

// Constructor
Sniper::Sniper(mtm::Team team, const int health, const int ammo, const int range, const int power):
        Character(team, health, ammo, range, power, MAX_STEPS, AMMO_PRICE) {
    this->counter = 1;
}


Sniper::Sniper(const Sniper& sniper):
        Character(sniper) {
    this->counter = sniper.counter;
}

void Sniper::load()
{
    this->ammo += LOADING_AMMO;
}

int Sniper::characterAttack(bool is_empty,int distance, const bool is_enemy, const mtm::GridPoint &src,
                            const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates)
{
    isTargetInRange(distance, this->range);
    Character::ammoPrice(this->ammo);
    if(is_enemy==false)
    {
        throw mtm::IllegalTarget();
    }
    this->ammo -= AMMO_PRICE;
    if(counter % TRIPLE_ATTACK == 0)
    {
        this->counter++;
        return ATTACK_BONUS * power;
    }
    this->counter++;
    return power;
}

int Sniper::characterAttacked(const int damage)
{
    this->health -= damage;
    return this->health;
}

void Sniper::isTargetInRange(int distance, int range)
{
    int max_distance = this->range;
    int min_distance = range/RANGE + (range%RANGE != 0);
    if (distance < min_distance || distance > max_distance )
    {
        throw mtm::OutOfRange();
    }
}

char Sniper::getTypeOfCharacter() {
    if(this->team == mtm::POWERLIFTERS)
    {
        return POWERLIFTERS_TYPE;
    }
    return CROSSFITTERS_TYPE;
}

Character* Sniper::clone() const {
    return new Sniper(*this);
}




