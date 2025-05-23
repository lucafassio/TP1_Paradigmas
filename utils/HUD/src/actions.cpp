#include "../headers/actions.hpp"
#include "../headers/display.hpp"
#include "../../../Ej2/characters/mages/headers/warlock.hpp"
#include "../../../Ej2/characters/character.hpp"
#include "../../../Ej3/headers/team.hpp"
#include "../../../Ej3/headers/funcs.hpp"

void createTeamLog(shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam){
    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()){
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    // Add headers if the file is empty
    logFile.seekp(0, ios::end);
    if (logFile.tellp() == 0) {
        logFile << "posTeam,selection,weapon,posRival,posTeammate1,PosTeammate2\n";
    }

    logFile.close();

    while(true){
        try{
            cout << "Select the character number (1-" << static_cast<int>(currentTeam->getMembers().size()) << ") to indicate his next move (0 to simulate battle): ";

            int characterNumber;
            cin >> characterNumber;

            if (characterNumber == 0) break; //salgo del bucle si elijo 0.
            
            //esto borra la ultima linea de la terminal.
            cout << "\033[A\33[2K";

            if (characterNumber < 1 || characterNumber > static_cast<int>(currentTeam->getMembers().size())){
                throw invalid_argument("Invalid character number."); return;
            }

            auto selectedCharacter = currentTeam->getMembers().at(characterNumber - 1);

            //esto no deberia fallar nunca.
            if (!selectedCharacter){
                throw invalid_argument("Character not found in the team."); return;
            }

            string characterType = selectedCharacter->getType();
            if (characterType == "Barbarian") logCreation_Barbarian_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Knight") logCreation_Knight_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Gladiator") logCreation_Gladiator_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Paladin") logCreation_Paladin_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Conjurer") logCreation_Conjurer_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Sorcerer") logCreation_Sorcerer_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Warlock") logCreation_Warlock_Case(selectedCharacter, currentTeam, targetTeam, characterNumber);
            else if (characterType == "Necromancer") logCreation_Necromancer_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Mercenary") logCreation_Mercenary_Case(selectedCharacter, targetTeam, characterNumber);
            else cout << "Invalid character type." << endl;
        }
        catch(const exception& e){
            cerr << e.what() << endl;
        }
    }
}

void logCreation_Barbarian_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Knight_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Gladiator_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Paladin_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Conjurer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Sorcerer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Warlock_Case(shared_ptr<Character> character, shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam, int characterNumber) {
    shared_ptr<Warlock> warlock = dynamic_pointer_cast<Warlock>(character);
    cout << "Select action for Warlock:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Use Soul Link" << endl;
    cout << "3. Use Born Again" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    //esto borra las ultimas 5 lineas de la terminal.
    for (int i = 0; i < 5; i++) {
        cout << "\033[A\33[2K";
    }

    switch (choice){
        case 1: logCreationCharacterAttacks(character, targetTeam, characterNumber); break;
        case 2: warlock->soulLink(currentTeam); break;
        case 3: warlock->bornAgain(currentTeam); break;
        default: cout << "Invalid choice. Turn skipped." << endl;
    }
}

void logCreation_Necromancer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Mercenary_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreationCharacterAttacks(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber) {
    cout << "Select the target number from the rival team: ";
    int targetNumber;
    cin >> targetNumber;

    //esto borra la ultima linea de la terminal.
    cout << "\033[A\33[2K";

    if (targetNumber < 1 || targetNumber > static_cast<int>(targetTeam->getMembers().size())) {
        cout << "Invalid target number." << endl;
        return;
    }

    auto weapons = character->inventory();
    shared_ptr<Weapon> selectedWeapon = nullptr;

    int weaponChoice = 0;
    if (weapons.first && weapons.second){
        cout << "Select weapon to use (1-2): ";
        cin >> weaponChoice;

        //esto borra la ultima linea de la terminal.
        cout << "\033[A\33[2K";

        if (weaponChoice < 1 || weaponChoice > 2){
            cout << "Invalid weapon choice." << endl;
            return;
        }
    }
    else if (weapons.first) weaponChoice = 1;
    else if (weapons.second) weaponChoice = 2;

    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()){
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    logFile << characterNumber << ",1," << weaponChoice << "," << targetNumber << ",,\n";

    logFile.close();
}

vector<int> readLogLine(string line){
    vector<int> result(6, -1); // Initialize with -1
    stringstream ss(line);
    string value;
    int index = 0;

    while (getline(ss, value, ',') && index < 6){
        try {
            result[index] = stoi(value);
        } catch (const invalid_argument&) {
            result[index] = -1; // Default to -1 if conversion fails
        }
        index++;
    }

    return result;
}

void readLogData(shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam){
    ifstream logFile("log.csv");
    if (!logFile.is_open()) {
        cerr << "Failed to open log.csv for reading." << endl;
        return;
    }

    vector<string> logLines;
    string line;
    // Skip the header line
    if (getline(logFile, line)){
        while (getline(logFile, line)){
            //saco la data de la linea.
            vector<int> data = readLogLine(line);

            //vuelvo a imprimir el campo de batalla.
            clearScreen();
            showBattleField(currentTeam, targetTeam);
            
            //imprimo las lineas anteriores sin ejecutar.
            for (int i = 0; i < static_cast<int>(logLines.size()); i++){
                cout << logLines[i];
            }

            //ejecuto e imprimo la accion siguiente. Agrego la linea al vector de lineas.
            logLines.push_back(excecuteAction(data, currentTeam, targetTeam));

            //agrego un delay de 2 segundos.
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    //muestro el estado final de la pelea.
    clearScreen();
    showBattleField(currentTeam, targetTeam);
    for (int i = 0; i < static_cast<int>(logLines.size()); i++){
        cout << logLines[i];
    }

    logFile.close();
}

string excecuteAction(vector<int> data, shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam){
    string logText;

    //extreaigo los datos del vector.
    int characterNumber = data[0];
    int action = data[1];
    int weaponChoice = data[2];
    int targetNumber = data[3];
    int numberTeammate1 = data[4]; //no se usa por ahora.
    int numberTeammate2 = data[5]; //no se usa por ahora.

    //agarro el personaje seleccionado y los posibles objetivos.
    shared_ptr<Character> selectedCharacter = currentTeam->getMembers().at(characterNumber - 1);

    shared_ptr<Character> targetCharacter = nullptr;
    if (targetNumber != -1) targetCharacter = targetTeam->getMembers().at(targetNumber - 1);

    shared_ptr<Character> targetTeammate1 = nullptr;
    if (numberTeammate1 != -1) targetTeammate1 = currentTeam->getMembers().at(numberTeammate1 - 1);

    shared_ptr<Character> targetTeammate2 = nullptr;
    if (numberTeammate2 != -1) targetTeammate2 = currentTeam->getMembers().at(numberTeammate2 - 1);

    //agarro el arma seleccionada.
    shared_ptr<Weapon> selectedWeapon = nullptr;
    if (weaponChoice == 1) selectedWeapon = selectedCharacter->inventory().first;
    if (weaponChoice == 2) selectedWeapon = selectedCharacter->inventory().second;

    //action == 1 representa atacar con un arma, para todos los personajes es lo mismo.
    if (action == 1) {logText = selectedCharacter->useWeapon(selectedWeapon, targetCharacter, targetTeam); return logText;}

    //handeleo los casos especificos de cada personaje.
    string characterType = selectedCharacter->getType();
    if (characterType == "Barbarian") return logText; //el barbaro no hace nada mas que atacar.
    else if (characterType == "Knight") return logText;
    else if (characterType == "Gladiator") return logText;
    else if (characterType == "Paladin") return logText;
    else if (characterType == "Conjurer") return logText;
    else if (characterType == "Sorcerer") return logText;
    else if (characterType == "Warlock") {excecute_Warlock_Action(selectedCharacter, currentTeam, action); return logText;}
    else if (characterType == "Necromancer") return logText;
    else if (characterType == "Mercenary") return logText;
    return logText; //en caso de que no se haya ejecutado nada, devuelvo un string vacio.
}

void excecute_Warlock_Action(shared_ptr<Character> warlockCharacter, shared_ptr<Team> warlockTeam, int action){
    shared_ptr<Warlock> warlock = dynamic_pointer_cast<Warlock>(warlockCharacter);
    if (action == 2) warlock->soulLink(warlockTeam);
    else if (action == 3) warlock->bornAgain(warlockTeam);
}