#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../../utils/data.hpp"

class Character;

class Weapon{
    public:
        virtual string getName() const = 0;
        virtual bool isCombat() const = 0;
        virtual int getDurability() const = 0;
        
        virtual string getMaterial() const = 0;
        virtual void use() = 0;
        
        virtual int attack() = 0;
        
        virtual ~Weapon() = default;
};

#endif // WEAPON_HPP
