#ifndef SORCERER_HPP
#define SORCERER_HPP

#include "../mage.hpp"

class Sorcerer final : public Mage {
private:
    SorcererType currentType;
    int cooldown;
    int switchCooldown;

    void elementalAttack(shared_ptr<Character> target);
    void elementalSpecial(shared_ptr<Character> target, shared_ptr<Team> team);

public:
    Sorcerer(string name);

    void changeElement(SorcererType newType);
    void attack(shared_ptr<Character> target);
    void special(shared_ptr<Character> target, shared_ptr<Team> team);
    
    void resetCooldown();
    void tickCooldown();
    bool specialReady() const;
    bool canChangeElement() const;

    string getType() const override;
};

#endif
