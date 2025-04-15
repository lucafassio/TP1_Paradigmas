#include "funcs.hpp"
// #include "team.cpp"
// #include "funcs.cpp"
// #include "factory.cpp"

class Team;

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

    cout << "========== Teams created. ==========" << endl;
    showTeamMembers(team1);
    cout << endl;
    showTeamMembers(team2);
    cout << endl;

    return 0;
}