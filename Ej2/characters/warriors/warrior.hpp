

#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#define INCLUDED_CORRECTLY

#include "../character.hpp"
#include "../../weapons/weapon.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Warrior : public Character {
protected:
    string name;
    int health;
    int armor;
    int combatBuff;
    pair<Weapon*, Weapon*> weapons;
    int BASE_DAMAGE=10;

public:
    Warrior(string name);

    string getName() const override;
    int getHealth() const override;
    int getArmor() const;
    int getBuff() const override;

    void reciveDamage(int dam) override;

    void addWeapon(Weapon *w) override;
    std::pair<Weapon*, Weapon*> inventory() const override;
    int useWeapon(Weapon* w, Character* op) = 0;
    
};

#endif // WARRIOR_HPP
