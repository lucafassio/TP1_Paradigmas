#ifndef MERCENARY_HPP
#define MERCENARY_HPP

#include "../warrior.hpp"

class Team;

class Mercenary: public Warrior {
private:
    int allysRemaining;
    shared_ptr<Team> currentTeam;

public:
    Mercenary(string name, shared_ptr<Team> currentTeam);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void entersTeam(shared_ptr<Team> team);
    void receiveDamage(int damage) override;
    void runAway();
    void betray(shared_ptr<Team> currentTeam, shared_ptr<Team> objective);
    string getInvisible();
    string recruitAlly();
    int getAllysRemaining() const;
};

#endif // MERCENARY_HPP