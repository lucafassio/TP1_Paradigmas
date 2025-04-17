#ifndef SWORD_HPP
#define SWORD_HPP

#include "../combat.hpp"

class Sword final: public Combat{
private:
    int sharpness;
    
    void setDamage(Material mat) override;
public:
    Sword(Material mat);
    Sword(const Sword& other);
    
    int attack();
    void sharpen();
    int getDamage() const;
    int getSharpness() const;
};

#endif // SWORD_HPP