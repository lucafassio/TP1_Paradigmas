#ifndef SPEAR_HPP
#define SPEAR_HPP

#include "../combat.hpp"
#include <string>
#include <iostream>
using namespace std;

class Spear final : public Combat{
private:
    int length;

    void setDamage(Material mat);
public:
    Spear(Material mat);

    int attack();
    int getDamage() const;
    int getLength() const;
};

#endif // SPEAR_HPP
