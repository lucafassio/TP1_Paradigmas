#ifndef SWORD_HPP
#define SWORD_HPP

#include "../combat.hpp"
#include <string>
#include <iostream>
using namespace std;

class Sword final : public Combat{
    private:
        int sharpness;
        
        void setDamage(Material mat);
    public:
        Sword(Material mat);
        
        int attack();
        void sharpen();
        int getDamage() const;
        int getSharpness() const;
};

#endif // SWORD_HPP