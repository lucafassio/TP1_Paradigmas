#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "../mage.hpp"

class Necromancer final : public Mage {
public:
    Necromancer(string name);

    void castSpell(const string& spellName) override;

    // Additional methods
    void raiseDead(const string& corpseName);
    void strengthenControl();
    void summonUndead();
    void curseEnemy();
};

#endif // NECROMANCER_HPP