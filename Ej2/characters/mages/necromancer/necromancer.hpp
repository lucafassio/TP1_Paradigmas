#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "../mage.hpp"

class Larry;

class Necromancer final : public Mage{
private:
    bool larryAlive = false;

public:
    Necromancer(string name);

    int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
    void raiseDead(shared_ptr<Team> currentTeam);
    void drainLife(shared_ptr<Character> target, shared_ptr<Team> targetTeam);
};

#endif // NECROMANCER_HPP