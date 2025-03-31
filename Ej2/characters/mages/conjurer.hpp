#ifndef CONJURER_HPP
#define CONJURER_HPP

#include <iostream>
#include <string>
using namespace std;

class Conjurer {
public:
    // Summons a creature
    virtual void summonCreature(const string& creatureName) = 0;

    // Returns the conjurer's summoning power
    virtual int getSummoningPower() const = 0;

    // Enhances the summoning power
    virtual void enhanceSummoningPower() = 0;

    virtual ~Conjurer() = default;
};

#endif // CONJURER_HPP
