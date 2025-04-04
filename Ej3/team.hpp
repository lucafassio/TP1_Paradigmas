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
#include <vector>

class Team {
    public:
        vector<Character*> members;  // Made public temporarily
        
        Team();

        Character* getMember(string name) const;
        friend class PersonajeFactory;
};

#endif // TEAM_HPP