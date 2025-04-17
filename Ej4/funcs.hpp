#include "../utils/data.hpp"

shared_ptr<Character> createPlayer1();

shared_ptr<Character> createPlayer2();

void showCurrentHealth(shared_ptr<Character> p1, shared_ptr<Character> p2);

int getWinner(Attack choice1, Attack choice2);

void fight(shared_ptr<Character> p1, shared_ptr<Character> p2);