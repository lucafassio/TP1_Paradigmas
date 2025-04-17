#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "../magic.hpp"

class Spellbook: public Magic{
private:
    vector<string> spells;

public:
    Spellbook(string name);
    Spellbook(const Spellbook& other);

    string use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber) override;
    void addClone(shared_ptr<Team> holderTeam, shared_ptr<Character> holder);
};

#endif // SPELLBOOK_HPP