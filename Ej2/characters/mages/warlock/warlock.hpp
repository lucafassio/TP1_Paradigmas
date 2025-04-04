#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "../mage.hpp"

class Warlock final : public Mage{
public:
    Warlock(string name);

    void castSpell(const string& spellName) override;

    // Additional methods
    void performRitual(const string& ritualName);
    int getDarkEnergy() const;
    void absorbDarkEnergy();
};

#endif // WARLOCK_HPP