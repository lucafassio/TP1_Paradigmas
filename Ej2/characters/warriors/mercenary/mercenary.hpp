#ifndef MERCENARY_HPP
#define MERCENARY_HPP

#include "../warrior.hpp"

class Team;

class Mercenary : public Warrior{
private:
    int allysRemaining;
    Team* currentTeam;

public:
    Mercenary(string name, Team* currentTeam);

    int useWeapon(Weapon* weapon, Character* traget, Team* targetTeam) override;
    void reciveDamage(int dam) override;
    void runAway();
    void betray(Team* currentTeam, Team* objective);
    void stealWeapon(Character* target);
    void getInvisible();
    void recruitAlly();
};

#endif // MERCENARY_HPP