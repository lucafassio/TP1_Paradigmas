#ifndef PALADIN_HPP
#define PALADIN_HPP

#include "../warrior.hpp"
#include <string>
#include <iostream>
using namespace std;

class Paladin final : public Warrior {
private:
    int faith;

public:
    Paladin(const string& name);
};

#endif // PALADIN_HPP