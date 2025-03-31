#ifndef MERCENARY_HPP
#define MERCENARY_HPP

#include <iostream>
#include <string>
using namespace std;

class Mercenary {
public:
    // Executes a contract
    virtual void executeContract(const string& contractDetails) = 0;

    // Returns the mercenary's combat skill level
    virtual int getCombatSkill() const = 0;

    // Trains to improve combat skills
    virtual void train() = 0;

    virtual ~Mercenary() = default;
};

#endif // MERCENARY_HPP
