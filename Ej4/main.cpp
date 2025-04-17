#include "funcs.hpp"
#include "../Ej3/funcs.hpp"

int main(){
    clearScreen();
    cout << "========== Ej 4: Epic (Rock/Paper/Scissors) Fight ==========" << endl;
    srand(time(nullptr));
    try{
        //creo los personajes, el player1 lo elige el usuario y el player2 es random.
        shared_ptr<Character> player1 = createPlayer1();
        shared_ptr<Character> player2 = createPlayer2();

        // Start the battle
        fight(player1, player2);
    } 
    catch (const invalid_argument& e){
        cout << e.what() << endl;
    }
    catch (const exception& e){
        cout << "An error occurred: " << e.what() << endl;
    }
    return 0;
}