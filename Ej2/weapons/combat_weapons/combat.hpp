#ifndef COMBAT_HPP
#define COMBAT_HPP

#include "../weapon.hpp"

enum Material{
    NONE = 0,
    WOOD = 59,
    STONE = 131,
    IRON = 250,
    GOLD = 32,
    DIAMOND = 1561
};

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

    virtual ~Combat();
};

#endif // COMBAT_HPP
