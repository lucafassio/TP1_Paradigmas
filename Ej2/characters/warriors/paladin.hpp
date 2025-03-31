#ifndef PALADIN_HPP
#define PALADIN_HPP

#include "warrior.hpp"
#include <string>
#include <iostream>
using namespace std;

class Paladin final : public Warrior {
private:
    int faith;

public:
    Paladin(const string& name, int health, int mana, int strength, int armor, int faith);

    void specialMove() override;

    // Additional methods
    void holyStrike();
    int getFaith() const;
    void increaseFaith();
    void healAllies();
};

#endif // PALADIN_HPP
