#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../warrior.hpp"

class Knight : public Warrior{
private:
    int armorLevel;
    
public:
    Knight(string name);
    virtual ~Knight() = default;
};

#endif // KNIGHT_HPP
