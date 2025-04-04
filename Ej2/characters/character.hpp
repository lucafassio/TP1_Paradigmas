#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <memory>
using namespace std;

class Weapon;

enum CharacterType{
    //mages
    CONJURER,
    NECRO,
    SORCERER,
    WARLOCK,

    //warriors
    BARBARIAN,
    GLADIATOR,
    KNIGHT,
    MERCENARY,
    PALADIN
};

enum Effect {
    REGENERATION,
    STRENGTH,
    BURNING,
    POISON,
    STUN,
    LUCK,
    IMMUNITY,
    INVISIBILITY
};

class Character{
public:
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getBuff() const = 0;
    virtual string getType() const = 0;

    virtual void reciveDamage(int dam) = 0;

    virtual void addWeapon(Weapon *w) = 0;
    virtual pair<Weapon*, Weapon*> inventory() const = 0;
    virtual int useWeapon(Weapon* weapon, Character* target) = 0;

    virtual void heal(int amount) = 0;
    virtual void applyEffect(Effect effect, int duration) = 0;
    virtual void effectUpdate() = 0;

    virtual ~Character() = default;
};

#endif // CHARACTER_HPP
