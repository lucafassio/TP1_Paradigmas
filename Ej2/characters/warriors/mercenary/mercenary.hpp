#ifndef MERCENARY_HPP
#define MERCENARY_HPP

#include "../warrior.hpp"

class Mercenary : public Warrior {
private:
    int combatSkill;
    
public:
    Mercenary(string name);
    void executeContract(const string& contractDetails);
    int getCombatSkill() const;
    void train();
};

#endif // MERCENARY_HPP
