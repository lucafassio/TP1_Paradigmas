#ifndef SORCERER_HPP
#define SORCERER_HPP

#include "../mage.hpp"

class Sorcerer final: public Mage {
private:
    SorcererType currentType;

    
public:
    Sorcerer(string name);

    string useWeapon(unique_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override; // Changed to unique_ptr

    void changeElement(SorcererType newType);    
    void elementalAttack(shared_ptr<Character> target);

    string getType() const override;
};

#endif
