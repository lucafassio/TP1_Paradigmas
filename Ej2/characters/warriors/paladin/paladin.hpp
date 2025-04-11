#ifndef PALADIN_HPP
#define PALADIN_HPP

#include "../warrior.hpp"

class Paladin : public Warrior {
private:
    int divineShieldCooldown;
    bool hasDivineShield;

public:
    Paladin(string name);

    int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void receiveDamage(int damage) override;

    void healingTeam(shared_ptr<Character> target1, shared_ptr<Character> target2);
    void divineShield();

    void endTurnUpdate(shared_ptr<Team> currentTeam) override;
};

#endif // PALADIN_HPP