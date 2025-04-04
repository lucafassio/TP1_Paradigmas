#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../weapon.hpp"

class Magic : public Weapon{
protected:
    string name;
    int durability;

public:
    Magic(int durability);

    string getName() const override;
    bool isCombat() const override;
    int getDurability() const override;
    
    string getMaterial() const = 0;
    virtual void use() = 0;

    int attack() override;

    virtual ~Magic() = default;
};

#endif // MAGIC_HPP
