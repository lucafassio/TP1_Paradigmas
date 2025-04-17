#ifndef AMULET_HPP
#define AMULET_HPP

#include "../magic.hpp"

class Character;

class Amulet final: public Magic{
    private:
        AmuletProp property;

    public:
        Amulet(AmuletProp prop);
        Amulet(const Amulet& other);
        
        string getType() const;

        string use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) override;
};

#endif // AMULET_HPP
