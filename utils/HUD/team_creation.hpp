#ifndef TEAM_CREATION_HPP
#define TEAM_CREATION_HPP

#include "../../Ej2/characters/character.hpp"
// #include "../../Ej2/characters/warriors/warrior.hpp"
// #include "../../Ej2/characters/mages/mage.hpp"
#include "../../Ej3/team.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

void displayTeamSlots(shared_ptr<Team> team);

void teamCreation(shared_ptr<Team> team);

#endif