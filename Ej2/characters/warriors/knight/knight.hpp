#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../warrior.hpp"

class Knight : public Warrior {
private:
    int turnsWithIronWill;
    int cooldownIronWill;
    bool ironWillActive;
    
public:
    Knight(string name);

    int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;

    void ironWill();
    void endTurnUpdate(shared_ptr<Team> currentTeam) override;
};

#endif
