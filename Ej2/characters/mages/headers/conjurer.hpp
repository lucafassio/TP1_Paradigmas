#ifndef CONJURER_HPP
#define CONJURER_HPP

#include "../mage.hpp"

class Conjurer : public Mage{
private:
    bool shielded;
    int cooldown;
    int empoweredDamage;

public:
    Conjurer(string name);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;

    void summonShield(); // bloquea daño 1 turno
    bool isShielded() const;
    void updateCooldown();

    void applyEffectTo(shared_ptr<Character> target, Effect effectType);

    void empowerAttribute(); // incrementa buff en 5 a costa de 10 HP
    bool canUseShield() const;
};

#endif