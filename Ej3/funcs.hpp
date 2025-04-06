#ifndef UTILS_HPP
#define UTILS_HPP

#include "factory.hpp"
#include "team.hpp"
#include "../Ej2/characters/character.hpp"

void showWarriorOptions();

void showMageOptions();

void showWeaponOptions();

void fullFillingWeapons(shared_ptr<Character> character, bool random);

void fullFillingTeam(shared_ptr<Team> team, int numWarriors, int numMages, bool random);

void showTeamMembers(shared_ptr<Team> team);

string getRandomName(CharacterType characterType);

#endif // UTILS_HPP