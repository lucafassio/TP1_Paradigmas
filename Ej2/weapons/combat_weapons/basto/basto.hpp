#ifndef BASTO_HPP
#define BASTO_HPP

#include "../combat.hpp"

class Basto final : public Combat{
private:
    int durabilityBoost;
    int damageBoost;
    Material reinforcement;

public:
    Basto();
    Basto(Material reinforcement);

    int attack();
    void reinforce(Material mat);
    int getDamage() const;
    void getReinforcement() const;
};

#endif // BASTO_HPP
