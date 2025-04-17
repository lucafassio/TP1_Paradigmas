#ifndef POTION_HPP
#define POTION_HPP

#include "../magic.hpp"

class Potion: public Magic{
private:
    PotionType type;
    bool thrown;

public:
    Potion(PotionType type);
    Potion(const Potion& other);

    string getType() const;
    string use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) override;
};

#endif // POTION_HPP