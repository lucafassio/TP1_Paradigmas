#ifndef TEAM_HPP
#define TEAM_HPP

#include "../utils/data.hpp"

class Character;
class Warlock;

class Team{
    private:
        string name;
        vector<shared_ptr<Character>> members;

    public:
        Team(string name);

        vector<shared_ptr<Character>> getMembers() const;
        shared_ptr<Character> getMember(string name) const;
        shared_ptr<Warlock> getWarlock() const;
        void loseMember(shared_ptr<Character> member);
        void showMembers() const;
        friend class Factory;
        friend class Mercenary;
        friend class Necromancer;
};

#endif // TEAM_HPP