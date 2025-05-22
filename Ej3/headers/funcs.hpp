#ifndef UTILS_HPP
#define UTILS_HPP

#include "../../utils/data.hpp"

class Character;

void clearScreen();

void showWarriorOptions();

void showMageOptions();

void showWeaponOptions();

void fullFillingWeapons(shared_ptr<Character> character, bool random);

void fullFillingTeam(shared_ptr<Team> team, int numWarriors, int numMages, bool random);

string getRandomName(CharacterType characterType);

#endif // UTILS_HPP