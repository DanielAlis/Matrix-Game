#include "Character.h"

Character::Character(mtm::Team team, int health,int ammo,int range,
                        int power, int max_steps, int ammo_price):
        team(team),
        health(health),
        ammo(ammo),
        range(range),
        power(power),
        max_steps(max_steps),
        ammo_price(ammo_price)
{
    if(range < 0 || health <= 0|| ammo < 0 ||  power < 0 )
    {
        throw mtm::IllegalArgument();
    }
}

Character::Character(const Character& character):
        team(character.team),
        health(character.health),
        ammo(character.ammo),
        range(character.range),
        power(character.power),
        max_steps(character.max_steps),
        ammo_price(character.ammo_price)
{}

void Character::isMovementLegal(int distance)
{
    if (distance > this->max_steps)
    {
        throw mtm::MoveTooFar();
    }
}

void Character::ammoPrice(int ammo)
{
    if (this->ammo_price > ammo)
    {
        throw mtm::OutOfAmmo();
    }
}

mtm::Team Character::getTeam() {
    return this->team;
}

void Character::isTargetInRange(int distance, int range)
{
    if (distance > range)
    {
        throw mtm::OutOfRange();
    }
}
