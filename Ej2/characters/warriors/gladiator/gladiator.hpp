#ifndef GLADIATOR_HPP
#define GLADIATOR_HPP

#include "../warrior.hpp"

class Gladiator : public Warrior {
private:
    int lastStandCooldown = 0;
    bool lastStandActive = false;

public:
    Gladiator(string name);

    int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;

    void receiveDamage(int dmg) override;
    void activateLastStand();
    bool isLastStandActive() const;

    void endTurnUpdate(shared_ptr<Team> = nullptr) override;
};

#endif
