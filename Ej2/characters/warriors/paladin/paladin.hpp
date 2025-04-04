#ifndef PALADIN_HPP
#define PALADIN_HPP

#include "../warrior.hpp"

class Paladin final : public Warrior {
private:
    int faith;

public:
    Paladin(string name);
};

#endif // PALADIN_HPP