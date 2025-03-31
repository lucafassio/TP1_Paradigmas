#ifndef DOUBLE_AXE_HPP
#define DOUBLE_AXE_HPP

#include "../combat.hpp"
#include <string>
#include <iostream>
using namespace std;

class DoubleAxe final : public Combat{
private:
    int weight;

    void setDamage(Material mat);
    void setWeight(Material mat);

    int getBonusProbability(Material mat) const;
public:
    DoubleAxe(Material mat);

    int attack();
    int getDamage() const;
    int getWeight() const;
};

#endif // DOUBLE_AXE_HPP
