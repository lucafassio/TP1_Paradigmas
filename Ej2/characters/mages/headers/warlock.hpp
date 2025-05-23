#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "../mage.hpp"

class Warlock final : public Mage {
private:
    int soulLinkCooldown;
    int ultimateCooldown;

public:
    vector<shared_ptr<Character>> linkedAllies;

    Warlock(string name);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> enemyTeam) override;
    void soulLink(shared_ptr<Team> ownTeam);
    void bornAgain(shared_ptr<Team> ownTeam);

    void updateCooldowns();
    void breakSoulLink();
};

#endif
