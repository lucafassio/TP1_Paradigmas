#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <fstream>
using namespace std;

#include "../Ej2/characters/character.hpp"

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
};

#endif // TEAM_HPP