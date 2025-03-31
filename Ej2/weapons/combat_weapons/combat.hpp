#ifndef COMBAT_HPP
#define COMBAT_HPP

#include "../weapon.hpp"
#include <string>
#include <iostream>
using namespace std;

enum Material{
    NONE=0,
    WOOD=59,
    STONE=131,
    IRON=250,
    GOLD=32,
    DIAMOND=1561
};

class Combat : public Weapon {
protected:
    Material material;
    int durability;
    int damage;
    string name;

public:
    Combat(Material dur);

    string getMaterial() const override;
    int getDurability() const override;
    string getName() const override;

    void repair(int ammount);
    void loseDurability(int amount);

    virtual int attack() = 0;
    virtual ~Combat(); // Remove override specifier
};

#endif // COMBAT_HPP
