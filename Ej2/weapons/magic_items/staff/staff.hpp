#ifndef STAFF_HPP
#define STAFF_HPP

#include "../magic.hpp"

class Staff : public Magic {
public:
    Staff(const string& name, int magicPower, int durability);
    int getWeight() const;
    void use();
    void castSpell(const string& spellName) override;
    int attack() override;
    void recharge();
    void breakStaff();
};

#endif // STAFF_HPP