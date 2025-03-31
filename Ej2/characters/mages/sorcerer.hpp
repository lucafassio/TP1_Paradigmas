#ifndef SORCERER_HPP
#define SORCERER_HPP

#include "mage.hpp"
#include <string>
#include <iostream>
using namespace std;

class Sorcerer final : public Mage {
public:
    Sorcerer(const string& name, int health, int mana, int magicPower, int spellSlots);

    void castSpell(const string& spellName) override;

    // Additional methods
    void summonFamiliar();
    void teleport();
    void enhanceSpell();
    void dispelMagic();
};

#endif // SORCERER_HPP
