#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../warrior.hpp"

class Knight : public Warrior {
    private:
        int timesWithIronWill;
        int cooldownIronWill;
        
    public:
        Knight(string name);

        string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) override;
        void receiveDamage(int damage) override;
        void ironWill();
        void endTurnUpdate() override;
};

#endif
