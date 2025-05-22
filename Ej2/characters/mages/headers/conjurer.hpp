#ifndef CONJURER_HPP
#define CONJURER_HPP

#include "../mage.hpp"

class Conjurer final: public Mage{
private:
    bool shielded;
    int cooldown;
    int empoweredDamage;

public:
    Conjurer(string name);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;

    void summonShield();
    bool isShielded() const;
    void updateCooldown();

    void applyEffectTo(shared_ptr<Character> target, Effect effectType);

    void empowerAttribute();
    bool canUseShield() const;
};

#endif