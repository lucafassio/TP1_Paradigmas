#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../weapon.hpp"
#include <string>
#include <iostream>
using namespace std;

class Magic : public Weapon {
protected:
    string name; 
    int magicPower;
    int durability;
    

public:
    Magic(const string& name, int magicPower, int durability);

    string getMaterial() const override;
    string getName() const override;
    bool isCombat() const override;

    // Shared methods for all magic items
    int getMagicPower() const;
    void enhanceMagicPower(int amount);
    void drainMagicPower(int amount);

    virtual void castSpell(const string& spellName) = 0;
    int attack() = 0;

    virtual ~Magic() = default;
};

#endif // MAGIC_HPP
