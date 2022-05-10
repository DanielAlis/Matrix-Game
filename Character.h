//
// Created by Alis Daniel on 19/06/2021.
//

#ifndef UNTITLED6_CHARACTER_H
#define UNTITLED6_CHARACTER_H

#include "Exceptions.h"

class Character {
public:
    mtm::Team team;
    int health;
    int ammo;
    int range;
    int power;
    int max_steps;
    int ammo_price;

    /** constructor: creates a character from the data.
     * @param team- the team it plays for.
     * @param health- its health.
     * @param range- the range of its attacks.
     * @param max_steps- the maximum amount of steps it can take.
     * @param ammo_price- the cost of attacking.
    */
    Character(mtm::Team team, int health,int ammo,int range,int power, int max_steps, int ammo_price);

    /** copy constructor: creates a character from the data.
     * @param character- the character it copies.
    */
    Character(const Character& character);

    /** isMovementLegal: checks if the movement is legal.
     * @param distance- the distance the character wants to walk.
    */
    virtual void isMovementLegal(int distance);

    /** ammoPrice: Checks if character has enough ammo to attack.
     * @param ammo- the amount of ammo it currently has.
    */
    virtual void ammoPrice(int ammo);

    /** isTargetInRange: Checks if the target is in attack range.
     * @param distance- the distance between the character and the place it wants to attack.
     * @param range- the range of the attacking character.
    */
    virtual void isTargetInRange(int distance, int range);

    /** getTeam: fetches the team of the current character.
     * @return
     * returns the team of the character.
    */
    virtual mtm::Team getTeam();

    // load: loads ammo to the character.
    virtual void load() = 0;

    /** characterAttack: the character attacks a location.
      * @param distance- the distance between this character and the attacked.
      * @param is_enemy- is the target an enemy or not.
      * @param src- where the character attacks from.
      * @param dst- the place that the attacker attacked.
      * @param attacked_coordinates-  a location in the attack radius.
     */
    virtual int characterAttack(const bool is_empty,int distance, const bool is_enemy, const mtm::GridPoint &src
                                , const mtm::GridPoint &dst, const mtm::GridPoint &attackers_coordinates) = 0 ;

    /** characterAttacked: the character is being attacked.
     * @param damage- the amount of damage being dealt to him.
    */
    virtual int characterAttacked(int damage) = 0;

    // clone: creates a copy of the character.
    virtual Character* clone() const = 0;

    /** getTypeOfCharacter: fetches the type character this is.
     * @return
     * returns the type of the character.
    */
    virtual char getTypeOfCharacter() = 0;
};

#endif //UNTITLED6_CHARACTER_H
