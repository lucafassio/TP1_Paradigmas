#ifndef LARRY_HPP
#define LARRY_HPP

#include "../mage.hpp"

//Larry stats
#define SKELETON_HEALTH 30
#define SKELETON_DAMAGE 6

class Larry : public Mage{
    private:
        int lifetimeRemaining = 2; //turnos restantes de vida.

    public:
        Larry();

        string getType() const override; 
        int useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;

        void loseLifetime();
};

#endif // LARRY_HPP