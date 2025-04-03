#ifndef TEAM_HPP
#define TEAM_HPP

#include "../Ej2/characters/character.hpp"
#include "../Ej2/weapons/weapon.hpp"
#include <vector>

class Team {
    public:
        vector<Character*> members;  // Made public temporarily
        
        Team(int num);

        Character* getMember(string name) const;
        friend class PersonajeFactory;
};

#endif // TEAM_HPP