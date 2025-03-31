#ifndef STAFF_HPP
#define STAFF_HPP

#include "magic.hpp"
#include <string>
#include <iostream>
using namespace std;

class Staff final : public Magic {
public:
    Staff(const string& name, int magicPower, int durability);

    int getWeight() const override;
    void use() override;
    void castSpell(const string& spellName) override;

    // Additional methods
    void recharge();
    void breakStaff();
};

#endif // STAFF_HPP
