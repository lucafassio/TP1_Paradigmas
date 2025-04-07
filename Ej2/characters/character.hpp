#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "../../utils/data.hpp"
#include "../weapons/weapon.hpp"
#include "../Ej3/team.hpp"

class Weapon;
class Team;

class Character{
public:
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getBuff() const = 0;
    virtual string getType() const = 0;

    virtual void heal(int amount) = 0;
    virtual void receiveDamage(int dam) = 0;

    virtual void addWeapon(shared_ptr<Weapon> w) = 0;
    virtual pair<shared_ptr<Weapon>, shared_ptr<Weapon>> inventory() const = 0;
    virtual int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) = 0;
    virtual void loseWeapon(shared_ptr<Weapon> weapon) = 0;

    //metodos para manejar efectos.
    virtual void applyEffect(Effect effect, int duration) = 0;
    virtual void effectUpdate(shared_ptr<Team> currentTeam) = 0;
    virtual void regenCase() = 0;
    virtual void strengthCase() = 0;
    virtual void burnCase() = 0;
    virtual void bleedCase() = 0;
    virtual void poisonCase() = 0;
    virtual void stunCase() = 0;
    virtual void luckCase() = 0;
    virtual void immunityCase() = 0;
    virtual void invisibilityCase() = 0;
    

    virtual ~Character() = default;
};

#endif // CHARACTER_HPP
