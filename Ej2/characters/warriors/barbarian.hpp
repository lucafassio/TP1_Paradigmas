#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP

#include "warrior.hpp"
#include <string>
#include <iostream>
using namespace std;

class Barbarian final : public Warrior {
public:
    Barbarian(const string& name, int health, int mana, int strength, int armor);

    void specialMove() override;

    // Additional methods
    void rageAttack();
    void intimidate();
    void berserkMode();
};

#endif // BARBARIAN_HPP
