#include "fight.hpp"
#include "../Ej3/funcs.hpp"

int fight(){
    cout << "========== Ej 4: Epic (Rock/Paper/Scissors) Fight ==========" << endl;
    srand(time(nullptr));
    while(true) try{
        string name;
        cout << "Enter characters name: ";
        cin.ignore();
        getline(cin, name);
        if (cin.fail()){
            cin.clear();
            cin.ignore(9999, '\n');
            throw invalid_argument("Please enter a valid name.");
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
        if (cin.fail()){
            cin.clear();
            cin.ignore(9999, '\n');
            throw invalid_argument("Please enter a number.") << endl;
        }
        
        shared_ptr<Character> player1 = nullptr;
        switch (choice){
            case 1: player1 = Factory::createCharacter(team1, BARBARIAN, name); break;
            case 2: player1 = Factory::createCharacter(team1, GLADIATOR, name); break;
            case 3: player1 = Factory::createCharacter(team1, KNIGHT, name); break;
            case 4: player1 = Factory::createCharacter(team1, MERCENARY, name); break;
            case 5: player1 = Factory::createCharacter(team1, PALADIN, name); break;
            case 6: player1 = Factory::createCharacter(team1, CONJURER, name); break;
            case 7: player1 = Factory::createCharacter(team1, NECRO, name); break;
            case 8: player1 = Factory::createCharacter(team1, SORCERER, name); break;
            case 9: player1 = Factory::createCharacter(team1, WARLOCK, name); break;
            case 10: player1 = Factory::createCharacter(team1, static_cast<CharacterType>(rand() % 9 + 1), name); break;
            default: throw invalid_argument("Invalid character selected."); break;
        }
        
        shared_ptr<Character> player2 = Factory::createCharacter(team2, BARBARIAN, "Maximus");

    }
    

    return 0;
}