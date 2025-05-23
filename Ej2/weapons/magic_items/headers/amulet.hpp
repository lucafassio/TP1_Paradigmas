#ifndef AMULET_HPP
#define AMULET_HPP

#include "../magic.hpp"

class Amulet final : public Magic{
    private:
        AmuletProp property;
        bool active;
        int cooldown;
        shared_ptr<Character> holder;

    public:
        Amulet(AmuletProp prop, shared_ptr<Character> holder);
        
        string getType() const;

        void setHolder(shared_ptr<Character> holder);

        string use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) override;
        void giveEffect();
};

#endif // AMULET_HPP
