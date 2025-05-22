#include "../headers/actions.hpp"

// Combat weapons and base
#include "../../Ej2/weapons/combat_weapons/combat.hpp"
#include "../../Ej2/weapons/combat_weapons/sword/sword.hpp"
#include "../../Ej2/weapons/combat_weapons/axe/axe.hpp"
#include "../../Ej2/weapons/combat_weapons/spear/spear.hpp"
#include "../../Ej2/weapons/combat_weapons/basto/basto.hpp"
#include "../../Ej2/weapons/combat_weapons/double_axe/double_axe.hpp"

// Magic items
#include "../../Ej2/weapons/magic_items/magic.hpp"
#include "../../Ej2/weapons/magic_items/amulet/amulet.hpp"
#include "../../Ej2/weapons/magic_items/potion/potion.hpp"
#include "../../Ej2/weapons/magic_items/spellbook/spellbook.hpp"
#include "../../Ej2/weapons/magic_items/staff/staff.hpp"

// Characters
#include "../../Ej2/characters/character.hpp"

// Warriors
#include "../../Ej2/characters/warriors/warrior.hpp"
#include "../../Ej2/characters/warriors/barbarian/barbarian.hpp"
#include "../../Ej2/characters/warriors/gladiator/gladiator.hpp"
#include "../../Ej2/characters/warriors/knight/knight.hpp"
#include "../../Ej2/characters/warriors/paladin/paladin.hpp"
#include "../../Ej2/characters/warriors/mercenary/mercenary.hpp"

// Mages
#include "../../Ej2/characters/mages/conjurer/conjurer.hpp"
#include "../../Ej2/characters/mages/sorcerer/sorcerer.hpp"
#include "../../Ej2/characters/mages/warlock/warlock.hpp"
#include "../../Ej2/characters/mages/necromancer/necromancer.hpp"

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

            if (selectedCharacter->getHealth() == 0){
                cout << selectedCharacter->getName() << " is dead." << endl;

                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
                continue; //skip to the next iteration.
            }

            string characterType = selectedCharacter->getType();
            if (characterType == "Barbarian") logCreation_Barbarian_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Knight") logCreation_Knight_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Gladiator") logCreation_Gladiator_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Paladin") logCreation_Paladin_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Conjurer") logCreation_Conjurer_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Sorcerer") logCreation_Sorcerer_Case(selectedCharacter, targetTeam, characterNumber);
            else if (characterType == "Warlock") logCreation_Warlock_Case(selectedCharacter, currentTeam, targetTeam, characterNumber);
            else if (characterType == "Necromancer") logCreation_Necromancer_Case(selectedCharacter, currentTeam, targetTeam, characterNumber);
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
    shared_ptr<Knight> knight = dynamic_pointer_cast<Knight>(character);
    cout << "Select action for Knight:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Use Iron Will" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    //esto borra las ultimas 4 lineas de la terminal.
    for (int i = 0; i < 4; i++) {
        cout << "\033[A\33[2K";
    }

    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()){
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    switch (choice){
        case 1: logCreationCharacterAttacks(character, targetTeam, characterNumber); break;
        case 2: 
            if (knight->getIronWillCooldown()){
                cout << "Iron Will is on cooldown (" << knight->getIronWillCooldown() << " turns reamining)." << endl;
                
                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
            }
            else logFile << characterNumber << ",2,,,,\n"; 
            break;
        default: cout << "Invalid choice." << endl; break;
    }

    logFile.close();
}

void logCreation_Gladiator_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber){
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Paladin_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber){
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Conjurer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber){
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Sorcerer_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber){
    logCreationCharacterAttacks(character, targetTeam, characterNumber);
}

void logCreation_Warlock_Case(shared_ptr<Character> character, shared_ptr<Team>, shared_ptr<Team> targetTeam, int characterNumber){
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

    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()){
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    switch (choice){
        case 1: logCreationCharacterAttacks(character, targetTeam, characterNumber); break;
        case 2: 
            if (warlock->getSoulLinkCooldown()){
                cout << "Soul Link is on cooldown (" << warlock->getSoulLinkCooldown() << " turns reamining)." << endl;
                
                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
            }
            else logFile << characterNumber << ",2,,,,\n"; 
            break;
        case 3:
            if (warlock->hasUsedBornAgain()) cout << warlock->getName() << "'ve already used Born Again." << endl;
            else logFile << characterNumber << ",3,,,,\n"; 
            break;
        default: cout << "Invalid choice." << endl; break;
    }

    logFile.close();
}

void logCreation_Necromancer_Case(shared_ptr<Character> character, shared_ptr<Team> currentTeam, shared_ptr<Team> targetTeam, int characterNumber){
    shared_ptr<Necromancer> necro = dynamic_pointer_cast<Necromancer>(character);
    cout << "Select action for Necromancer:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Drain life from enemy" << endl;
    cout << "3. Raise from dead" << endl;
    cout << "4. Revive a teammate" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    //esto borra las ultimas 6 lineas de la terminal.
    for (int i = 0; i < 6; i++) {
        cout << "\033[A\33[2K";
    }

    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()){
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    switch (choice){
        case 1: logCreationCharacterAttacks(character, targetTeam, characterNumber); break;
        case 2: 
            cout << "Select the target you want to drain life: ";
            int targetNumber;
            cin >> targetNumber;

            if (targetNumber < 1 || targetNumber > static_cast<int>(targetTeam->getMembers().size())){
                cout << "Invalid target number." << endl;

                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
                return;
            }
            else if (!targetTeam->getMembers().at(targetNumber - 1)->getHealth()){
                cout << "Target is dead." << endl;

                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
                return;
            }
            else logFile << characterNumber << ",2,," << targetNumber << ",,\n";
            break;
        case 3: logFile << characterNumber << ",3,,,,\n"; break;
        case 4:
            cout << "Select the target you want to revive: ";
            int targetTeammate;
            cin >> targetTeammate;

            if (currentTeam->getMembers().at(targetTeammate - 1)->getHealth()){
                cout << "Target is already alive." << endl;
                
                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
                return;
            }

            if (targetTeammate < 1 || targetTeammate > static_cast<int>(targetTeam->getMembers().size())){
                cout << "Invalid target number." << endl;

                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
                return;
            }
            else logFile << characterNumber << ",4,,," << targetTeammate << ",\n";
            break;
        default: 
            cout << "Invalid choice." << endl;

            //espero dos segundos y borro la linea de arriba.
            this_thread::sleep_for(chrono::seconds(2));
            cout << "\033[A\33[2K";
            break;
    }

    logFile.close();
}

void logCreation_Mercenary_Case(shared_ptr<Character> character, shared_ptr<Team> targetTeam, int characterNumber){
    shared_ptr<Mercenary> mercenary = dynamic_pointer_cast<Mercenary>(character);
    cout << "Select action for Warlock:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Call an ally" << endl;
    cout << "3. Disapear" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    //esto borra las ultimas 5 lineas de la terminal.
    for (int i = 0; i < 5; i++){
        cout << "\033[A\33[2K";
    }

    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()){
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    switch (choice){
        case 1: logCreationCharacterAttacks(character, targetTeam, characterNumber); break;
        case 2: 
            if (!mercenary->getAllysRemaining()){
                cout << "You run out of friends." << endl;
                
                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
            }
            else logFile << characterNumber << ",2,,,,\n"; 
            break;
        case 3:
            if (mercenary->hasEffect(INVISIBILITY)){
                cout << "Mercenary is already invisible." << endl;
                
                //espero dos segundos y borro la linea de arriba.
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[A\33[2K";
            }
            else logFile << characterNumber << ",4,,,,\n";
            break;
        default: cout << "Invalid choice." << endl; break;
    }

    logFile.close();
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

    int weaponChoice = 0;
    if (character->inventory().first && character->inventory().second) {
        cout << "Select weapon to use (1-2): ";
        cin >> weaponChoice;

        //esto borra la ultima linea de la terminal.
        cout << "\033[A\33[2K";

        if (weaponChoice < 1 || weaponChoice > 2) {
            cout << "Invalid weapon choice." << endl;
            return;
        }
    } else if (character->inventory().first) {
        weaponChoice = 1;
    } else if (character->inventory().second) {
        weaponChoice = 2;
    }

    ofstream logFile("log.csv", ios::app);
    if (!logFile.is_open()) {
        cerr << "Failed to open log.csv for writing." << endl;
        return;
    }

    logFile << characterNumber << ",1," << weaponChoice << "," << targetNumber << ",,\n";

    logFile.close();
}

vector<int> readLogLine(string line){
    vector<int> result(6, -1);
    stringstream ss(line);
    string value;
    int index = 0;

    while (getline(ss, value, ',') && index < 6){
        try {
            result[index] = stoi(value);
        } catch (const invalid_argument&) {
            result[index] = -1;
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

    //extraigo los datos del vector.
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

    //action == 1 representa atacar con un arma, para todos los personajes es lo mismo.
    if (action == 1){
        if (!weaponChoice) selectedCharacter->useWeapon(nullptr, targetCharacter, targetTeam);
        else logText = weaponChoice == 1 ? selectedCharacter->useWeapon(selectedCharacter->inventory().first, targetCharacter, targetTeam) : selectedCharacter->useWeapon(selectedCharacter->inventory().second, targetCharacter, targetTeam);

    }
    //handeleo los casos especificos de cada personaje.
    string characterType = selectedCharacter->getType();
    if (characterType == "Barbarian") return logText; //el barbaro no hace nada mas que atacar.
    else if (characterType == "Knight") return excecute_Knight_Action(selectedCharacter, action);
    else if (characterType == "Gladiator") return logText;
    else if (characterType == "Paladin") return logText;
    else if (characterType == "Conjurer") return logText;
    else if (characterType == "Sorcerer") return logText;
    else if (characterType == "Warlock") return excecute_Warlock_Action(selectedCharacter, currentTeam, action);
    else if (characterType == "Necromancer") return excecute_Necromancer_Action(selectedCharacter, currentTeam, targetCharacter, targetTeammate1, action);
    else if (characterType == "Mercenary") return excecute_Mercenary_Action(selectedCharacter, action);
    return logText; //en caso de que no se haya ejecutado nada, devuelvo un string vacio.
}

string excecute_Knight_Action(shared_ptr<Character> knightCharacter, int action){
    shared_ptr<Knight> knight = dynamic_pointer_cast<Knight>(knightCharacter);
    if (action == 2) return knight->ironWill(); 
    return ""; 
}

string excecute_Warlock_Action(shared_ptr<Character> warlockCharacter, shared_ptr<Team> warlockTeam, int action){
    shared_ptr<Warlock> warlock = dynamic_pointer_cast<Warlock>(warlockCharacter);
    if (action == 2) return warlock->soulLink(warlockTeam); 
    else if (action == 3) return warlock->bornAgain(warlockTeam);
    return ""; 
}

string excecute_Necromancer_Action(shared_ptr<Character> necromancerCharacter, shared_ptr<Team> currentTeam, shared_ptr<Character> targetCharacter, shared_ptr<Character> targetTeammate, int action){
    shared_ptr<Necromancer> necromancer = dynamic_pointer_cast<Necromancer>(necromancerCharacter);
    if (action == 2) return necromancer->drainLife(targetCharacter); 
    else if (action == 3) return necromancer->raiseDead(currentTeam);
    else if (action == 4) return necromancer->reviveTeammate(targetTeammate);
    return ""; 
}

string excecute_Mercenary_Action(shared_ptr<Character> mercenaryCharacter, int action){
    shared_ptr<Mercenary> mercenary = dynamic_pointer_cast<Mercenary>(mercenaryCharacter);
    if (action == 2) return mercenary->recruitAlly(); 
    else if (action == 3) return mercenary->getInvisible();
    return ""; 
}