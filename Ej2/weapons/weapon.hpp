#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <iostream>
using namespace std;

class Weapon {
    public:
        virtual string getMaterial() const = 0;
        virtual string getName() const = 0;
        virtual int attack() = 0;
        virtual bool isCombat() const = 0;
        
        virtual ~Weapon() = default;
};

#endif // WEAPON_HPP
