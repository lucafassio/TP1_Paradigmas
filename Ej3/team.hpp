#ifndef TEAM_HPP
#define TEAM_HPP

#include "../utils/data.hpp"

class Character;

class Team{
    private:
        vector<shared_ptr<Character>> members;

    public:
        Team();

        vector<shared_ptr<Character>> getMembers() const;
        shared_ptr<Character> getMember(string name) const;
        void loseMember(shared_ptr<Character> member);
        void showMembers() const;
        friend class Factory;
        friend class Mercenary;
        friend class Necromancer;
};

#endif // TEAM_HPP