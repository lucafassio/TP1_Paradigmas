#ifndef GLADIATOR_HPP
#define GLADIATOR_HPP

#include <iostream>
#include <string>
using namespace std;

class Gladiator {
public:
    // Performs a crowd-pleasing move
    virtual void performMove(const string& moveName) = 0;

    // Returns the gladiator's popularity level
    virtual int getPopularity() const = 0;

    // Increases the gladiator's popularity
    virtual void increasePopularity() = 0;

    virtual ~Gladiator() = default;
};

#endif // GLADIATOR_HPP
