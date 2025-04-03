#ifndef CONJURER_HPP
#define CONJURER_HPP

#include "../mage.hpp"

class Conjurer : public Mage {
public:
    Conjurer(const string& name);
    Conjurer(const string& name, int health, int mana, int magicPower, int spellSlots);

    void castSpell(const string& spellName) override;

    // Additional methods
    void summonCreature(const string& creatureName);
    int getSummoningPower() const;
    void enhanceSummoningPower();
};

#endif // CONJURER_HPP