#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <memory>
#include <string>
#include <vector>
using namespace std;

void createTeamLog(shared_ptr<Team> currentTeam, shared_ptr<Team> rivalTeam);

void logCreationCharacterAttacks(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);

// Updated function declarations for each character type
void logCreation_Barbarian_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Knight_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Gladiator_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Paladin_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Conjurer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Sorcerer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Warlock_Case(shared_ptr<Character> character, shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Necromancer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);
void logCreation_Mercenary_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber);

vector<int> readLogLine(string line);
void readLogData(shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam);

string excecuteAction(vector<int> data, shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam);
void excecute_Warlock_Action(shared_ptr<Character> warlockCharacter, shared_ptr<Team> warlockTeam, int action);

#endif // ACTIONS_HPP