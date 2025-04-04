#ifndef STAFF_HPP
#define STAFF_HPP

#include "../magic.hpp"

class Staff : public Magic {
public:
    Staff(string name, int durability);

    string getMaterial() const override;
    void use() override;
};

#endif // STAFF_HPP