#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>
using namespace std;

class Warlock {
public:
    // Performs a dark ritual
    virtual void performRitual(const string& ritualName) = 0;

    // Returns the warlock's dark energy level
    virtual int getDarkEnergy() const = 0;

    // Absorbs dark energy
    virtual void absorbDarkEnergy() = 0;

    virtual ~Warlock() = default;
};

#endif // WARLOCK_HPP
