#ifndef COMBAT_HPP
#define COMBAT_HPP

#include "../weapon.hpp"

class Combat: public Weapon{
protected:
    Material material;
    int durability;
    int damage;
    string name;

    Combat(Material dur);
    virtual void setDamage(Material mat) = 0;
public:
    

    string getMaterial() const;
    string getName() const override;
    bool isCombat() const override;
    
    int getDurability() const;
    void repair(int amount);

    virtual int attack() = 0;
    virtual string use(shared_ptr<Team> targetTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) override;
};

#endif // COMBAT_HPP
