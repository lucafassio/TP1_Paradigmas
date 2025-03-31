#include "axe.hpp"
#include <cstdlib> // For rand()

Axe::Axe(Material mat): 
    Combat(mat) {
        setDamage(mat);
        setWeight(mat);
        name = this->getMaterial() + " Axe";
}

void Axe::setDamage(Material mat){
    switch (mat){
        case NONE: break;
        case WOOD: this->damage=5; break;
        case STONE: this->damage=6; break;
        case IRON: this->damage=7; break;
        case GOLD: this->damage=5; break;
        case DIAMOND: this->damage=8; break;
    }
}

void Axe::setWeight(Material mat){
    switch (mat){
        case NONE: break;
        case WOOD: this->weight=4; break;
        case STONE: this->weight=8; break;
        case IRON: this->weight=10; break;
        case GOLD: this->weight=6; break;
        case DIAMOND: this->weight=14; break;
    }
}

int Axe::attack(){
    if (this->durability<=0){
        cout << "Axe is broken!" << endl;
        return 0;
    }
    if (this->durability==1) cout << "Axe broke!" << endl;
    this->durability--;
    int bonusDamage=(rand()%100<30) ? this->weight/2 : 0;
    return this->damage+bonusDamage;
}

int Axe::getDamage() const {
    return this->damage;
}

int Axe::getWeight() const {
    return this->weight;
}
