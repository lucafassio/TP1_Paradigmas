#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../weapon.hpp"
#include <string>
#include <iostream>
using namespace std;

class Magic : public Weapon{
protected:
    string name;
    int magicPower;
    int durability;

public:
    Magic(int magicPower, int durability);

    string getMaterial() const = 0;
    string getName() const override;
    bool isCombat() const override;
    int getDurability() const override;

    virtual void use(string spellName) = 0;

    virtual ~Magic() = default;
};

#endif // MAGIC_HPP
