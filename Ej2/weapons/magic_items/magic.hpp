#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../weapon.hpp"

class Magic: public Weapon{
protected:
    string name;
    int duration;
    bool reusable;
    int cooldown;

    Magic(int duration, bool reusable, int cooldown);
public:
    string getName() const override;
    bool isCombat() const override;
    int getDuration() const;
    int attack() override;
    void decreaseCooldown();

    virtual string use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) = 0;
};

#endif // MAGIC_HPP
