#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <iostream>
using namespace std;

class Weapon {
    public:
        virtual string getMaterial() const = 0;
        virtual int getDurability() const = 0;
        virtual string getName() const = 0;

        virtual ~Weapon() = default; // Add virtual destructor
};

#endif // WEAPON_HPP
