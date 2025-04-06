#include "funcs.hpp"

class Team;

int main(){
    cout << "========== Ej 3: Factory ==========" << endl;
    srand(time(nullptr));
    int numWarriors = rand() % 5 + 3; //numero entre 3 y 7.
    int numMages = rand() % 5 + 3; //numero entre 3 y 7.

    cout << "Both teams will have " << numWarriors << " warriors and " << numMages << " mages.";

    //creo los dos equipos
    shared_ptr<Team> team1 = std::make_shared<Team>();
    shared_ptr<Team> team2 = std::make_shared<Team>();

    cout << endl << "First team will be created by hand." << endl;
    fullFillingTeam(team1, numWarriors, numMages, false);

    cout << endl << "Second team will be randomly generated" << endl;
    fullFillingTeam(team2, numWarriors, numMages, true);

    cout << "========== Teams created. ==========" << endl;
    cout << "Team 1:" << endl;
    showTeamMembers(team1);
    cout << endl;
    showTeamMembers(team2);
    cout << endl;

    return 0;
}