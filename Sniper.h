//
// Created by Alis Daniel on 19/06/2021.
//

#ifndef UNTITLED6_SNIPER_H
#define UNTITLED6_SNIPER_H

#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"

class Sniper : public Character {
    int counter;
public:
    Sniper(mtm::Team team, const int health, const int ammo, const int range, const int power);
    Sniper(const Sniper& sniper);
    void isTargetInRange(int distance, int range) override;
    void load() override;
    int characterAttack(const bool is_empty, int distance, const bool is_enemy, const mtm::GridPoint &src,
                        const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates) override;
    int characterAttacked( int damage) override;
    char getTypeOfCharacter() override;
    Character* clone() const override;
};
#endif //SNIPER_H


#endif //UNTITLED6_SNIPER_H
