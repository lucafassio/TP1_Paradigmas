#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "../data.hpp"

string toUpperCase(const string& str);

string effectToString(Effect effect);

string getHealthBar(int currentHealth, int maxHealth);

string getManaBar(int mana, int maxMana);

string getEmptyManaBar();

string getCombinedInventoryString(shared_ptr<Character> leftChar, shared_ptr<Character> rightChar);

void showCharactersInfo(shared_ptr<Character> leftChar, shared_ptr<Character> rightChar);

void showSingleCharacterInfo(shared_ptr<Character> character, bool isLeft);

void showBattleField(shared_ptr<Team> leftTeam, shared_ptr<Team> rightTeam);

#endif // DISPLAY_HPP