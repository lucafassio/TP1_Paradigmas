#ifndef SORCERER_HPP
#define SORCERER_HPP

#include "../mage.hpp"

class Sorcerer final : public Mage {
public:
    Sorcerer(string name);

    void castSpell(const string& spellName) override;

    // Additional methods
    void summonFamiliar();
    void teleport();
    void enhanceSpell();
    void dispelMagic();
};

#endif // SORCERER_HPP