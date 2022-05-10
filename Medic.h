

#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"

class Medic: public Character {
    /** isMe: Check if the medic is attacking itself (medic cannot attack itself)
    * @param src- the source of the attack medic.
    * @param dst- the destination of the attacked character .
    *
    * @return
    * Throws IllegalTarget if the medic is attacking itself.
    */
    static void isMe(const mtm::GridPoint &src, const mtm::GridPoint &dst);
public:
    Medic(mtm::Team team, const int health, const int ammo, const int range, const int power);
    void load() override;
    int characterAttack(const bool is_empty, int distance, const bool is_enemy, const mtm::GridPoint &src,
                        const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates) override;
    int characterAttacked(const int damage) override;
    char getTypeOfCharacter() override;
    Character* clone() const override;
};

#endif

