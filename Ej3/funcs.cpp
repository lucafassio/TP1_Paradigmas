#include "funcs.hpp"
#include "../Ej2/characters/character.hpp"
#include "factory.hpp"
#include "team.hpp"


//esto esta sacado de internet, es para limpiar la terminal nomas.
void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void showWarriorOptions(){
    cout << "Warrior options:" << endl;
    cout << "1. Barbarian" << endl;
    cout << "2. Gladiator" << endl;
    cout << "3. Knight" << endl;
    cout << "4. Mercenary" << endl;
    cout << "5. Paladin" << endl;
}

void showMageOptions(){
    cout << "Mage options:" << endl;
    cout << "1. Conjurer" << endl;
    cout << "2. Necromancer" << endl;
    cout << "3. Sorcerer" << endl;
    cout << "4. Warlock" << endl;
}

void showWeaponOptions(){
    cout << "Weapon options:" << endl;
    cout << "1. Axe" << endl;
    cout << "2. Basto" << endl;
    cout << "3. Double Axe" << endl;
    cout << "4. Spear" << endl;
    cout << "5. Sword" << endl;
    cout << "6. Amulet" << endl;
    cout << "7. Potion" << endl;
    cout << "8. Spellbook" << endl;
    cout << "9. Staff" << endl;
}

string getRandomName(CharacterType characterType){
    string filepath;
    switch (characterType){
        case BARBARIAN: filepath = "utils/character_names/barbarian.txt"; break;
        case GLADIATOR: filepath = "utils/character_names/gladiator.txt"; break;
        case KNIGHT: filepath = "utils/character_names/knight.txt"; break;
        case MERCENARY: filepath = "utils/character_names/mercenary.txt"; break;
        case PALADIN: filepath = "utils/character_names/paladin.txt"; break;
        case CONJURER: filepath = "utils/character_names/conjurer.txt"; break;
        case NECRO: filepath = "utils/character_names/necromancer.txt"; break;
        case SORCERER: filepath = "utils/character_names/sorcerer.txt"; break;
        case WARLOCK: filepath = "utils/character_names/warlock.txt"; break;
        default: cout << "Invalid character type!" << endl; return ""; break;
    }

    //abro el archivo con los nombres y leo una linea al azar.
    //todos los archivos tienen 30 nombres asi que no se puede pasar.
    ifstream file(filepath);
    int randomLine = rand() % 30; //numero entre 0 y 29.
    string name;
    for (int i = 0; i < randomLine; i++) getline(file, name);
    getline(file, name); //por si sale randomLine == 0.
    file.close();
    return name;
}

void fullFillingWeapons(shared_ptr<Character> character, bool random) {
    clearScreen();
    cout << "========== Ej 3: Factory ==========" << endl;
    //defino cuantas armas va a llevar el guerrero creado.
    int numWeapons = rand() % 3; //numero entre 0 y 2.
    vector<Material> mats = {NONE, WOOD, STONE, IRON, GOLD, DIAMOND};
    cout << character->getName() << " will carry " << numWeapons << " weapons." << endl;
    for (int i = 0; i < numWeapons; i++){
        try {
            int selectedWeapon;

            if (!random){
                //muestro las opciones que hay
                showWeaponOptions();
                cout << endl << "> ";
                cin >> selectedWeapon;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(9999, '\n');
                    throw invalid_argument("Invalid input. Please enter a number.");
                }
            }
            else selectedWeapon = rand() % 9 + 1; //numero entre 1 y 9.

            //meto el arma correspondiente.
            switch (selectedWeapon - 1) {
                case AXE: Factory::createAndAddWeaponToCharacter(character, AXE, mats[rand() % 5 + 1]); break;
                case BASTO:Factory::createAndAddWeaponToCharacter(character, BASTO, mats[rand() % 6]); break;
                case DOUBLE_AXE:Factory::createAndAddWeaponToCharacter(character, DOUBLE_AXE, mats[rand() % 5 + 1]); break;
                case SPEAR:Factory::createAndAddWeaponToCharacter(character, SPEAR, mats[rand() % 5 + 1]); break;
                case SWORD:Factory::createAndAddWeaponToCharacter(character, SWORD, mats[rand() % 5 + 1]); break;
                case AMULET:Factory::createAndAddWeaponToCharacter(character, AMULET, static_cast<AmuletProp>(rand() % 5)); break;
                case POTION:Factory::createAndAddWeaponToCharacter(character, POTION, static_cast<PotionType>(rand() % 6)); break;
                case SPELLBOOK:Factory::createAndAddWeaponToCharacter(character, SPELLBOOK, NONE); break;
                case STAFF:Factory::createAndAddWeaponToCharacter(character, STAFF, NONE); break;
                default: throw invalid_argument("Invalid weapon type!"); break;
            }

            clearScreen();
            cout << "========== Ej 3: Factory ==========" << endl;
            cout << character->getName() << " now has " << character->inventory().first->getName() << ", select another weapon." << endl;
        } 
        catch (bad_alloc& e){
            cout << "Memory allocation failed: " << e.what() << endl;
            return;
        } 
        catch (invalid_argument& e){
            cout << e.what() << endl;
            i--;

            //espero dos segundos y limpio la terminal.
            this_thread::sleep_for(chrono::seconds(2));
            clearScreen();
            cout << "========== Ej 3: Factory ==========" << endl;
            if (character->inventory().first) cout << character->getName() << " now has " << character->inventory().first->getName() << ", select another weapon." << endl;
            else cout << character->getName() << " will carry " << numWeapons << " weapons." << endl;
            continue;
        } 
        catch (exception& e){
            cout << e.what() << endl;
            return;
        }
    }
}

void fullFillingTeam(shared_ptr<Team> team, int numWarriors, int numMages, bool random){
    //primero meto los guerreros.
    for (int i = 0; i < numWarriors; i++){
        try{
            int selectedWarrior;
            shared_ptr<Character> warrior = nullptr;

            if (!random){

                //muestro las opciones que hay
                showWarriorOptions();
                cout << endl << "> ";
                cin >> selectedWarrior;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(9999, '\n');
                    throw invalid_argument("Invalid input. Please enter a number.");
                }
            }
            else selectedWarrior = rand() % 5 + 1; //numero entre 1 y 5
            
            //meto el guerrero correspondiente
            switch (selectedWarrior - 1){ //esta vez no le erre Juani.
                case BARBARIAN: warrior = Factory::createCharacter(BARBARIAN, getRandomName(BARBARIAN)); break;
                case GLADIATOR: warrior = Factory::createCharacter(GLADIATOR, getRandomName(GLADIATOR)); break;
                case KNIGHT: warrior = Factory::createCharacter(KNIGHT, getRandomName(KNIGHT)); break;
                case MERCENARY: warrior = Factory::createCharacter(MERCENARY, getRandomName(MERCENARY)); break;
                case PALADIN: warrior = Factory::createCharacter(PALADIN, getRandomName(PALADIN)); break;
                default: throw invalid_argument("Invalid warrior selected (choose from 1 to 5)"); break;
            }

            //para cada personaje agrego las armas
            fullFillingWeapons(warrior, random);

            //agrego el guerrero al equipo.
            Factory::addCharacterToTeam(team, warrior);

            //si todo sale bien, limpio la terminal.
            clearScreen();
            cout << "========== Ej 3: Factory ==========" << endl;
        }
        catch(const std::bad_alloc& e){
            cout << "Memory allocation failed: " << e.what() << endl;
            return;
        }
        catch(invalid_argument &e){
            cout << e.what() << endl;
            i--;

            //espero dos segundos y limpio la terminal.
            //this_thread::sleep_for(chrono::seconds(2));
            clearScreen();
            cout << "========== Ej 3: Factory ==========" << endl;
            continue;
        }
        catch (exception& e){
            cout << e.what() << endl;
            return;
        }
    }

    //repito el proceso con los magos.
    for (int i = 0; i < numMages; i++){
        try{
            int selectedMage;
            shared_ptr<Character> mage = nullptr;

            if (!random){

                //muestro las opciones que hay
                showMageOptions();
                cout << endl << "> ";
                cin >> selectedMage;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(9999, '\n');
                    throw invalid_argument("Invalid input. Please enter a number.");
                }
            }
            else selectedMage = rand() % 4 + 1; //numero entre 1 y 4.

            //le sumo 4 porque ahi arrancan los magos en el enum.
            switch (selectedMage + 4){
                case CONJURER: mage = Factory::createCharacter(CONJURER, getRandomName(CONJURER)); break;
                case NECRO: mage = Factory::createCharacter(NECRO, getRandomName(NECRO)); break;
                case SORCERER: mage = Factory::createCharacter(SORCERER, getRandomName(SORCERER)); break;
                case WARLOCK: mage = Factory::createCharacter(WARLOCK, getRandomName(WARLOCK)); break;
                default: throw invalid_argument("Invalid mage selected (choose from 1 to 4)"); break;
            }

            //para cada mago agrego las armas.
            fullFillingWeapons(mage, random);

            //agrego el mago al equipo.
            Factory::addCharacterToTeam(team, mage);

            //si todo sale bien, limpio la terminal.
            clearScreen();
            cout << "========== Ej 3: Factory ==========" << endl;
        }
        catch (const std::bad_alloc& e){
            cout << "Memory allocation failed: " << e.what() << endl;
            return;
        }
        catch(invalid_argument &e){
            cout << e.what() << endl;
            i--;

            //espero dos segundos y limpio la terminal.
            this_thread::sleep_for(chrono::seconds(2));
            clearScreen();
            cout << "========== Ej 3: Factory ==========" << endl;
            continue;
        }
        catch (const std::exception& e){
            cout << "An error occurred: " << e.what() << endl;
            return;
        }
    }
}