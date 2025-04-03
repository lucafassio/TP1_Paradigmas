#include "sword.hpp"

Sword::Sword(Material mat): 
    Combat(mat), sharpness(0){
        setDamage(mat);
        name = this->getMaterial() + " Sword";
}

void Sword::setDamage(Material mat){
    switch (mat){
        case NONE: break;
        case WOOD: this->damage = 4; break;
        case STONE: this->damage = 5; break;
        case IRON: this->damage = 6; break;
        case GOLD: this->damage = 4; break;
        case DIAMOND: this->damage = 7; break;
    }
}

int Sword::attack(){
    if (this->durability <= 0) {
        cout << "Sword is broken!" << endl;
        return 0;
    }
    if (this->durability == 1) cout << "Sword broke!" << endl;
    this->durability--;
    return this->damage + this->sharpness;
}

void Sword::sharpen(){
    sharpness++;
    if (sharpness > 5) {
        sharpness = 5;
        cout << "Sword is already at maximum sharpness!" << endl;
        return;
    }
    cout << "Sword sharpened! Current sharpness: " << sharpness << endl;
}

int Sword::getDamage() const {
    return this->damage;
}

int Sword::getSharpness() const {
    return this->sharpness;
}