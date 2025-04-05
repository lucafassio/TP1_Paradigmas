#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "../warrior.hpp"

class Barbarian final : public Warrior {
private:
    int rageAttacksLeft=0;
    const double RAGE_CHANCE=0.2;
    const double RAGE_DAMAGE_MULTIPLIER=1.7;

public:
    Barbarian(string name);
    int useWeapon(Weapon* w, Character* op, Team* targetTeam) override;
    bool isInRage() const;
    void decreaseRageTurns();

    friend class Amulet;
};

#endif // BARBARIAN_HPP
