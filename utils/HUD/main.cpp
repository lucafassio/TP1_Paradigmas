#include "display.cpp"
#include "team_creation.cpp"
#include "actions.cpp"
#include "../../Ej3/team.cpp"
#include "../../Ej3/funcs.cpp"
#include "../../Ej3/factory.cpp"

#include <thread>
#include <chrono>

int main(){
    clearScreen();
    srand(time(nullptr));
    int numWarriors = rand() % 5 + 3; //numero entre 3 y 7.
    int numMages = rand() % 5 + 3; //numero entre 3 y 7.

    shared_ptr<Team> team1 = make_shared<Team>("Team 1");
    shared_ptr<Team> team2 = make_shared<Team>("Team 2");

    fullFillingTeam(team1, numWarriors, numMages, true);
    fullFillingTeam(team2, numWarriors, numMages, true);

    cout << "========== Teams created. ==========" << endl;
    showTeamMembers(team1);
    cout << endl;
    showTeamMembers(team2);
    cout << endl;

    clearScreen();

    showBattleField(team1, team2);

    clearScreen();

    shared_ptr<Team> team3 = make_shared<Team>("Team 3");
    shared_ptr<Team> team4 = make_shared<Team>("Team 4");

    teamCreation(team3);
    fullFillingTeam(team4, 3, 2, true);

    clearScreen();

    showBattleField(team3, team4);

    //ESTO ES UN TURNO
    createTeamLog(team3, team4);
    clearScreen();
    readLogData(team3, team4);
    remove("log.csv");
    //HASTA ACA

    showBattleField(team4, team3);

    return 0;
}