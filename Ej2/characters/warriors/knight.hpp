#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <iostream>
#include <string>
using namespace std;

class Knight {
public:
    // Performs a shield bash
    virtual void shieldBash() = 0;

    // Returns the knight's armor level
    virtual int getArmorLevel() const = 0;

    // Repairs the knight's armor
    virtual void repairArmor() = 0;

    virtual ~Knight() = default;
};

#endif // KNIGHT_HPP
