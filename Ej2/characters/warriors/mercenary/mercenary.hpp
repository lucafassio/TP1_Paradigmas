#ifndef MERCENARY_HPP
#define MERCENARY_HPP

#include "../warrior.hpp"

class Team;

class Mercenary : public Warrior{
private:
    int allysRemaining;
    shared_ptr<Team> currentTeam;

public:
    Mercenary(string name, shared_ptr<Team> currentTeam);

    int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void receiveDamage(int dam) override;
    void runAway();
    void betray(shared_ptr<Team> currentTeam, shared_ptr<Team> objective);
    void stealWeapon(shared_ptr<Character> target);
    void getInvisible();
    void recruitAlly();
};

#endif // MERCENARY_HPP