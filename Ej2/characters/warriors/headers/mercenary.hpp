#ifndef MERCENARY_HPP
#define MERCENARY_HPP

#include "../warrior.hpp"

class Mercenary : public Warrior{
private:
    int allysRemaining;
    shared_ptr<Team> currentTeam;

public:
    Mercenary(string name, shared_ptr<Team> currentTeam);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void entersTeam(shared_ptr<Team> team);
    void receiveDamage(int dam) override;
    void runAway();
    void betray(shared_ptr<Team> currentTeam, shared_ptr<Team> objective);
    void stealWeapon(shared_ptr<Character> target);
    void getInvisible();
    void recruitAlly();
};

#endif // MERCENARY_HPP