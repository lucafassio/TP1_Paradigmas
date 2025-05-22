#ifndef TEAM_HPP
#define TEAM_HPP

#include "../../utils/data.hpp"

class Team{
    private:
        string name;
        vector<shared_ptr<Character>> members;

    public:
        Team(string name);

        string getName() const;
        vector<shared_ptr<Character>> getMembers() const;
        shared_ptr<Character> getMember(string name) const;
        shared_ptr<Warlock> getWarlock() const;
        void loseMember(shared_ptr<Character> member);
        void showMembers() const;
        void sortMembersByType();

        friend class Factory;
        friend class Mercenary;
        friend class Necromancer;
        friend class Spellbook;
};

#endif // TEAM_HPP