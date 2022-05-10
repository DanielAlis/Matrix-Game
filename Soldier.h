#ifndef SOLDIER_H
#define SOLDIER_H

#include "Character.h"

class Soldier: public Character {
    /** isLine: Check if the character is attacking in a line (solider can only attack in a straight line)
    * @param src- the source of the attack solider.
    * @param dst- the destination of the attacked character .
    *
    * @return
    * Throws IllegalTarget if the solider is not attacking in a straight line.
    */
    void isLine(const mtm::GridPoint &src, const mtm::GridPoint &dst);
public:
    Soldier(mtm::Team team, const int health, const int ammo, const int range, const int power);
    void load() override;
    int characterAttack(const bool is_empty, int distance, const bool is_enemy, const mtm::GridPoint &src,
                        const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates) override;
    int characterAttacked(const int damage) override;
    Character* clone() const override;
    char getTypeOfCharacter() override;
};

#endif

