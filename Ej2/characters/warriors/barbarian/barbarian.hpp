#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "../warrior.hpp"
#include <memory>

class Barbarian final : public Warrior {
private:
    int rageAttacksLeft=0;
    const double RAGE_CHANCE=0.2;
    const double RAGE_DAMAGE_MULTIPLIER=1.7;

public:
    Barbarian(string name);
    int useWeapon(shared_ptr<Weapon> w, shared_ptr<Character> op, shared_ptr<Team> targetTeam) override;
    bool isInRage() const;
    void decreaseRageTurns();

    friend class Amulet;
};

#endif // BARBARIAN_HPP
