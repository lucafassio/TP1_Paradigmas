#include "headers/funcs.hpp"
#include "headers/team.hpp"
#include "../utils/HUD/display.hpp"

int main(){
    clearScreen();
    cout << "========== Ej 3: Factory ==========" << endl;
    srand(time(nullptr));
    int numWarriors = rand() % 5 + 3; //numero entre 3 y 7.
    int numMages = rand() % 5 + 3; //numero entre 3 y 7.

    cout << "Both teams will have " << numWarriors << " warriors and " << numMages << " mages.";

    //creo los dos equipos
    shared_ptr<Team> team1 = make_shared<Team>("Team 1");
    shared_ptr<Team> team2 = make_shared<Team>("Team 2");

    cout << endl << "First team will be created by hand." << endl;
    fullFillingTeam(team1, numWarriors, numMages, false);

    cout << endl << "Second team will be randomly generated" << endl;
    fullFillingTeam(team2, numWarriors, numMages, true);

    clearScreen();
    showBattleField(team1, team2);

    return 0;
}