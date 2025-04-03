#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "../mage.hpp"
#include <string>
#include <iostream>
using namespace std;

class Necromancer final : public Mage {
public:
    Necromancer(const string& name);
    Necromancer(const string& name, int health, int mana, int magicPower, int spellSlots);

    void castSpell(const string& spellName) override;

    // Additional methods
    void raiseDead(const string& corpseName);
    void strengthenControl();
    void summonUndead();
    void curseEnemy();
};

#endif // NECROMANCER_HPP