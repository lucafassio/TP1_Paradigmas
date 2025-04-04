#ifndef POTION_HPP
#define POTION_HPP

#include "../magic.hpp"

class Potion : public Magic {
private:
    string type;
    bool expired;

public:
    Potion(string type, int durability);

    string getMaterial() const override;
    void use() override;
};

#endif // POTION_HPP