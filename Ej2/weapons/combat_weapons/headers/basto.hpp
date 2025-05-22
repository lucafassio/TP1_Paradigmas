#ifndef BASTO_HPP
#define BASTO_HPP

#include "../combat.hpp"

class Basto final: public Combat{
private:
    int durabilityBoost;
    int damageBoost;
    Material reinforcement;

    void setDamage(Material mat) override;
public:
    Basto(Material reinforcement);
    Basto(const Basto& other);

    int attack() override;
    void reinforce(Material mat);
    int getDamage() const;
    void getReinforcement() const;
};

#endif // BASTO_HPP
