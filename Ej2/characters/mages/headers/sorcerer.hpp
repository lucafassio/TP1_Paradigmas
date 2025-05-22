#ifndef SORCERER_HPP
#define SORCERER_HPP

#include "../mage.hpp"

class Sorcerer final: public Mage {
private:
    SorcererType currentType;

    
public:
    Sorcerer(string name);

    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override; // Changed to shared_ptr

    void changeElement(SorcererType newType);    
    void elementalAttack(shared_ptr<Character> target);

    string getType() const override;
};

#endif
