#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "../warrior.hpp"

class Barbarian final: public Warrior {
private:
    const double RAGE_DAMAGE_MULTIPLIER = 1.7;

public:
    Barbarian(string name);
    string useWeapon(shared_ptr<Weapon> w, shared_ptr<Character> op, shared_ptr<Team> targetTeam) override;
};

#endif 
