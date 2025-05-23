#include "utils/data.hpp"
#include "utils/HUD/headers/display.hpp"
#include "utils/HUD/headers/team_creation.hpp"
#include "utils/HUD/headers/actions.hpp"
#include "Ej2/characters/character.hpp"
#include "Ej3/headers/team.hpp"
#include "Ej3/headers/funcs.hpp"
#include "Ej3/headers/factory.hpp"

int main(){
    clearScreen();
    srand(time(nullptr));
    int numWarriors = rand() % 5 + 3; //numero entre 3 y 7.
    int numMages = rand() % 5 + 3; //numero entre 3 y 7.

    shared_ptr<Team> team1 = make_shared<Team>("Team 1");
    shared_ptr<Team> team2 = make_shared<Team>("Team 2");

    fullFillingTeam(team1, numWarriors, numMages, true);
    fullFillingTeam(team2, numWarriors, numMages, true);

    team1->getMembers().at(0)->applyEffect(STRENGTH, 2);
    team1->getMembers().at(0)->applyEffect(STUN, 2);
    team1->getMembers().at(1)->applyEffect(SCARED, 2);
    team1->getMembers().at(2)->applyEffect(BLEEDING, 2);
    team1->getMembers().at(2)->applyEffect(IMMUNITY, 2);
    team1->getMembers().at(2)->applyEffect(INVISIBILITY, 2);
    team1->getMembers().at(4)->applyEffect(MANA_LEECH, 2);
    team1->getMembers().at(4)->applyEffect(BURNING, 2);

    team2->getMembers().at(0)->applyEffect(STRENGTH, 2);
    team2->getMembers().at(0)->applyEffect(STUN, 2);
    team2->getMembers().at(1)->applyEffect(SCARED, 2);
    team2->getMembers().at(2)->applyEffect(BLEEDING, 2);
    team2->getMembers().at(2)->applyEffect(IMMUNITY, 2);
    team2->getMembers().at(2)->applyEffect(INVISIBILITY, 2);
    team2->getMembers().at(4)->applyEffect(MANA_LEECH, 2);
    team2->getMembers().at(4)->applyEffect(BURNING, 2);

    clearScreen();
    showBattleField(team1, team2);

    cout << "========== Teams created. ==========" << endl;
    showBattleField(team1, team2);

    clearScreen();

    shared_ptr<Team> team3 = make_shared<Team>("Team 3");
    shared_ptr<Team> team4 = make_shared<Team>("Team 4");

    clearScreen();
    showBattleField(team3, team2);

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
    createTeamLog(team4, team3);
    clearScreen();
    readLogData(team4, team3);
    remove("log.csv");

    showBattleField(team3, team4);

    return 0;
}
