#ifndef MAGE_HPP
#define MAGE_HPP

#include "../character.hpp"
#include <string>
#include <iostream>
using namespace std;

class Mage : public Character {
protected:
    string name;
    int health;
    int mana;
    int magicPower;
    int spellSlots;

public:
    Mage(const string& name, int health, int mana, int magicPower, int spellSlots);

    string getName() const override;
    int getHealth() const override;
    int getMana() const override;

    int getMagicPower() const;
    int getSpellSlots() const;
    void rechargeMana(int amount);
    void enhanceMagicPower(int amount);

    virtual void castSpell(const string& spellName) override;
    virtual void attack() override;
    virtual void defend() override;

    virtual ~Mage() = default;
};

#endif // MAGE_HPP
