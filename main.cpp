#include "Ej2/weapons/combat_weapons/sword/sword.hpp"

int main(){
    Sword s(DIAMOND);
    cout << "Sword damage: " << s.attack() << endl;
    s.sharpen();
    cout << "Sword damage after sharpening: " << s.attack() << endl;
    return 0;
}