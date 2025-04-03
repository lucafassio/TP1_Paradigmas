#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "../mage.hpp"

class Warlock final : public Mage {
public:
    Warlock(const string& name);
    Warlock(const string& name, int health, int mana, int magicPower, int spellSlots);

    void castSpell(const string& spellName) override;

    // Additional methods
    void performRitual(const string& ritualName);
    int getDarkEnergy() const;
    void absorbDarkEnergy();
};

#endif // WARLOCK_HPP