#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "../mage.hpp"
#include "larry.hpp"

class Necromancer final: public Mage {
private:
    int larrysCounter = 0;

public:
    Necromancer(string name);

    string useWeapon(unique_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    string raiseDead(shared_ptr<Team> currentTeam);
    string drainLife(shared_ptr<Character> target);
    string reviveTeammate(shared_ptr<Character> target);
};

#endif // NECROMANCER_HPP