#ifndef AXE_HPP
#define AXE_HPP

#include "../combat.hpp"

class Axe final: public Combat{
private:
    int weight;

    void setDamage(Material mat) override;
    void setWeight(Material mat);
public:
    Axe(Material mat);
    Axe(const Axe& other);

    int attack() override;
    int getDamage() const;
    int getWeight() const;
};

#endif // AXE_HPP
