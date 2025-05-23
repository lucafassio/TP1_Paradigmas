#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "../mage.hpp"

class Necromancer final : public Mage {
private:
    int larrysCounter = 0;

public:
    Necromancer(string name);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void raiseDead(shared_ptr<Team> currentTeam);
    void drainLife(shared_ptr<Character> target, shared_ptr<Team> targetTeam);
    void reviveTeammate(shared_ptr<Character> target);
};

#endif // NECROMANCER_HPP