#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "../mage.hpp"

class Warlock final: public Mage{
private:
    int soulLinkCooldown;
    bool bornAgainUsed = false;

public:
    vector<shared_ptr<Character>> linkedAllies;

    Warlock(string name);

    string useWeapon(unique_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> enemyTeam) override;
    string soulLink(shared_ptr<Team> ownTeam);
    int getSoulLinkCooldown() const;
    string bornAgain(shared_ptr<Team> ownTeam);
    bool hasUsedBornAgain() const;

    void updateCooldowns();
    void breakSoulLink();
};

#endif // WARLOCK_HPP
