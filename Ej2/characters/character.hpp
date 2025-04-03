#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../weapons/weapon.hpp"

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Character {
public:
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getBuff() const = 0;

    virtual void reciveDamage(int dam) = 0;

    virtual void addWeapon(Weapon *w) = 0;
    virtual std::pair<Weapon*, Weapon*> inventory() const = 0;
    virtual int useWeapon(Weapon* w, Character* op) = 0;
};

#endif // CHARACTER_HPP
