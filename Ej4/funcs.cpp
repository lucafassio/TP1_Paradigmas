#include "funcs.hpp"
#include "../Ej2/characters/character.hpp"
#include "../Ej3/headers/funcs.hpp"
#include "../Ej3/headers/factory.hpp"

shared_ptr<Character> createPlayer1(){
    string name;
    cout << "Enter characters name: ";
    getline(cin, name);
    while (cin.fail()){
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Please enter a valid name." << endl;
    }

    //el jugador 1 elige personaje y arma.
    cout << "Player 1, choose your character:" << endl
        << "1. Barbarian" << endl
        << "2. Gladiator" << endl
        << "3. Knight" << endl
        << "4. Mercenary" << endl
        << "5. Paladin" << endl
        << "6. Conjurer" << endl
        << "7. Necromancer" << endl
        << "8. Sorcerer" << endl
        << "9. Warlock" << endl
        << "10. Random" << endl;

    int choice;
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 10) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Please enter a valid option (1-10)." << endl;
        cout << "Player 1, choose your character:" << endl
            << "1. Barbarian" << endl
            << "2. Gladiator" << endl
            << "3. Knight" << endl
            << "4. Mercenary" << endl
            << "5. Paladin" << endl
            << "6. Conjurer" << endl
            << "7. Necromancer" << endl
            << "8. Sorcerer" << endl
            << "9. Warlock" << endl
            << "10. Random" << endl;
        cin >> choice;
    }
    
    shared_ptr<Character> player1;
    switch (choice){
        case 1: player1 = Factory::createCharacter(BARBARIAN, name); break;
        case 2: player1 = Factory::createCharacter(GLADIATOR, name); break;
        case 3: player1 = Factory::createCharacter(KNIGHT, name); break;
        case 4: player1 = Factory::createCharacter(MERCENARY, name); break;
        case 5: player1 = Factory::createCharacter(PALADIN, name); break;
        case 6: player1 = Factory::createCharacter(CONJURER, name); break;
        case 7: player1 = Factory::createCharacter(NECRO, name); break;
        case 8: player1 = Factory::createCharacter(SORCERER, name); break;
        case 9: player1 = Factory::createCharacter(WARLOCK, name); break;
        case 10: player1 = Factory::createCharacter(static_cast<CharacterType>(rand() % 9), name); break;
        default: throw invalid_argument("Invalid character selected."); break;
    }

    return player1;
}

shared_ptr<Character> createPlayer2(){
    CharacterType type = static_cast<CharacterType>(rand() % 9);
    shared_ptr<Character> player2 = Factory::createCharacter(type, getRandomName(type));
    Factory::createAndAddWeaponToCharacter(player2, static_cast<WeaponType>(rand() % 9), NONE);

    cout << "Player 2, your character is: " << player2->getName() << " (" << player2->getType() << ")" << endl;

    return player2;
}

void showCurrentHealth(shared_ptr<Character> p1, shared_ptr<Character> p2) {
    cout << p1->getName() << " (" << p1->getType() << ") tiene " << p1->getHealth() << " HP y " << p2->getName() << " (" << p2->getType() << ") tiene " << p2->getHealth() << " HP." << endl;
}

int getWinner(Attack choice1, Attack choice2) {
    if (choice1 == choice2) return 0;

    if ((choice1 == GOLPE_FUERTE && choice2 == GOLPE_RAPIDO) ||
        (choice1 == GOLPE_RAPIDO && choice2 == DEFENSA_Y_GOLPE) ||
        (choice1 == DEFENSA_Y_GOLPE && choice2 == GOLPE_FUERTE)) return 1;
    else return 2;
}

void fight(shared_ptr<Character> player1, shared_ptr<Character> player2){
    //clearScreen();
    cout << "========== THE FIGHT STARTS ==========" << endl;
    while (player1->getHealth() && player2->getHealth()){
        //muestro la vida de cada jugador.
        showCurrentHealth(player1, player2);

        //pido al usuario que elija un ataque.
        int choice;
        cout << "Su opción: (1) Golpe Fuerte, (2) Golpe Rápido, (3) Defensa y Golpe: ";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Please enter a valid option (1-3)." << endl;
            cout << "Su opción: (1) Golpe Fuerte, (2) Golpe Rápido, (3) Defensa y Golpe: ";
            cin >> choice;
        }
        clearScreen();

        //se elige un ataque aleatorio para el jugador 2 y veo quien gana
        int winner = getWinner(static_cast<Attack>(choice), static_cast<Attack>(rand() % 3 + 1));

        //muestro quien gano y hago el daño correspondiente.
        if (winner==1){
            player2->receiveDamage(10);
            cout << player1->getName() << " (" << player1->getType() << ") ataca a " << 
                    player2->getName() << " (" << player2->getType() << ") y hace 10 puntos de daño." << endl;
        }
        else if (winner==2){
            player1->receiveDamage(10);
            cout << player2->getName() << " (" << player2->getType() << ") ataca a " << 
                    player1->getName() << " (" << player1->getType() << ") y hace 10 puntos de daño." << endl;
        } 
        else cout << "Ambos eligieron el mismo ataque, es un empate." << endl;

    }

    cout << "========== GAME OVER ==========" << endl;
    if (!player1->getHealth()) cout << player2->getName() << " won." << endl;
    else cout << player1->getName() << " won." << endl;
}
