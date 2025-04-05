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
using namespace std;

#include "../Ej2/characters/character.hpp"
#include "../Ej2/weapons/weapon.hpp"

class Team{
    private:
        vector<Character*> members;

    public:
        Team();

        Character* getMember(string name) const;
        void loseMember(Character* member);
        void showMembers() const;
        friend class PersonajeFactory;
        friend class Mercenary;
};

#endif // TEAM_HPP