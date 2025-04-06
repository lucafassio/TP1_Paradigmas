#ifndef COMBAT_HPP
#define COMBAT_HPP

#include "../weapon.hpp"
#include "../../../utils/enums_data.hpp"

class Combat : public Weapon{
protected:
    Material material;
    int durability;
    int damage;
    string name;

public:
    Combat(Material dur);

    string getMaterial() const override;
    string getName() const override;
    bool isCombat() const override;
    
    int getDurability() const;
    void repair(int amount);
    void loseDurability(int amount);

    virtual int attack() = 0;
    
    void use() override;
};

#endif // COMBAT_HPP
