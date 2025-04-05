#ifndef NECROMANCER_HPP
#define NECROMANCER_HPP

#include "../mage.hpp"

//Skelly stats
#define SKELETON_HEALTH 30
#define SKELETON_DAMAGE 6

struct Skelly{
    int health;
    int damage;

    Skelly(): health(SKELETON_HEALTH), damage(SKELETON_DAMAGE){};
};


class Necromancer final : public Mage{
private:
    bool skellyAlive = false;

public:
    Necromancer(string name);

    int useWeapon(Weapon* weapon, Character* target, Team* targetTeam) override;
    void raiseDead();
};

#endif // NECROMANCER_HPP