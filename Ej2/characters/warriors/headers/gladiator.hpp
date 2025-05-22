#ifndef GLADIATOR_HPP
#define GLADIATOR_HPP

#include "../warrior.hpp"

class Gladiator: public Warrior{
private:
    bool lastStandActive = false;
    bool gloryUsed = false;
    bool gloryActive = false;

public:
    Gladiator(string name);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void receiveDamage(int dmg) override;
    void blastOfGlory(shared_ptr<Team> ownTeam, shared_ptr<Team> enemyTeam);
};

#endif
