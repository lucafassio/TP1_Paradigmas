#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>
using namespace std;

class Character {
public:
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual int getMana() const = 0;
    virtual void attack() = 0;
    virtual void defend() = 0;

    virtual ~Character() = default;
};

#endif // CHARACTER_HPP
