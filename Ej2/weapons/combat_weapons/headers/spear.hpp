#ifndef SPEAR_HPP
#define SPEAR_HPP

#include "../combat.hpp"

class Spear final: public Combat{
private:
    int length;

    void setDamage(Material mat) override;
public:
    Spear(Material mat);
    Spear(const Spear& other);

    int attack();
    int getDamage() const;
    int getLength() const;
};

#endif // SPEAR_HPP
