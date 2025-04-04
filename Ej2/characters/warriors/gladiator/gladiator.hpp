#ifndef GLADIATOR_HPP
#define GLADIATOR_HPP

#include "../warrior.hpp"

class Gladiator final: public Warrior {
private:
    int popularity;

public:
    Gladiator(string name);

    void performMove(const string& moveName);
    int getPopularity() const;
    void increasePopularity();
};

#endif // GLADIATOR_HPP
