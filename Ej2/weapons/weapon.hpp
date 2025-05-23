#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../../utils/data.hpp"

class Weapon{
    public:
        virtual string getName() const = 0;
        virtual bool isCombat() const = 0;

        virtual int attack() = 0;
        virtual string use(shared_ptr<Team> targetTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) = 0;
        
        virtual ~Weapon() = default;
};

#endif // WEAPON_HPP
