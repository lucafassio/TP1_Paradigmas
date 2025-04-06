#include "fight.hpp"

int fight(){

    shared_ptr<Character> player1 = Factory::createCharacter(team1, BARBARIAN, "Conan");
    shared_ptr<Character> player2 = Factory::createCharacter(team2, BARBARIAN, "Maximus");

    // Show team members
    team1->showMembers();
    team2->showMembers();

    return 0;
}