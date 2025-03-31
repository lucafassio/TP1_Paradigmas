#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../weapon.hpp"
#include <string>
#include <iostream>
using namespace std;

class Magic : public Weapon {
protected:
    int magicPower;
    int durability;
    string name;

public:
    Magic(const string& name, int magicPower, int durability);

    string getName() const override;
    int getDurability() const override;
    void repair() override;

    // Shared methods for all magic items
    int getMagicPower() const;
    void enhanceMagicPower(int amount);
    void drainMagicPower(int amount);

    virtual void castSpell(const string& spellName) = 0;

    virtual ~Magic() = default;
};

#endif // MAGIC_HPP
