#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include "../character.hpp"
#include <string>
#include <iostream>
using namespace std;

class Warrior : public Character {
protected:
    string name;
    int health;
    int mana;
    int strength;
    int armor;

public:
    Warrior(const string& name, int health, int mana, int strength, int armor);

    string getName() const override;
    int getHealth() const override;
    int getMana() const override;

    int getStrength() const;
    int getArmor() const;
    void enhanceStrength(int amount);
    void repairArmor(int amount);

    virtual void attack() override;
    virtual void defend() override;
    virtual void specialMove() = 0;

    virtual ~Warrior() = default;
};

#endif // WARRIOR_HPP
