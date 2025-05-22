#ifndef DOUBLE_AXE_HPP
#define DOUBLE_AXE_HPP

#include "../combat.hpp"

class DoubleAxe final: public Combat{
private:
    int weight;

    void setDamage(Material mat) override;
    void setWeight(Material mat);

    int getBonusProbability(Material mat) const;
public:
    DoubleAxe(Material mat);
    DoubleAxe(const DoubleAxe& other);

    int attack() override;
    int getDamage() const;
    int getWeight() const;
};

#endif // DOUBLE_AXE_HPP
