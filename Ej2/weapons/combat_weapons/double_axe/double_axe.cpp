#include "double_axe.hpp"
#include <cstdlib>

DoubleAxe::DoubleAxe(Material mat): 
    Combat(mat){
        setDamage(mat);
        setWeight(mat);
        name = this->getMaterial() + " Double Axe";
}

void DoubleAxe::setDamage(Material mat){
    switch (mat){
        case NONE: break;
        case WOOD: this->damage = 7; break;
        case STONE: this->damage = 8; break;
        case IRON: this->damage = 9; break;
        case GOLD: this->damage = 7; break;
        case DIAMOND: this->damage = 10; break;
    }
}

void DoubleAxe::setWeight(Material mat){
    switch (mat){
        case NONE: break;
        case WOOD: this->weight = 4; break;
        case STONE: this->weight = 8; break;
        case IRON: this->weight = 10; break;
        case GOLD: this->weight = 6; break;
        case DIAMOND: this->weight = 14; break;
    }
}

int DoubleAxe::getBonusProbability(Material mat) const {
    switch (mat){
        case NONE: return 0;
        case WOOD: return 50;
        case STONE: return 20;
        case IRON: return 15;
        case GOLD: return 70;
        case DIAMOND: return 30;
        default: return 0;
    }
}

int DoubleAxe::attack(){
    if (this->durability <= 0) {
        cout << "Double Axe is broken!" << endl;
        return 0;
    }
    if (this->durability == 1) cout << "Double Axe broke!" << endl;
    this->durability--;

    int totalDamage = this->damage + this->weight / 2;

    if (rand() % 100 < getBonusProbability(this->material)) {
        cout << "Bonus attack triggered! Additional damage: " << this->damage / 2 << endl;
        totalDamage += this->damage / 2;
    }

    return totalDamage;
}

int DoubleAxe::getDamage() const {
    return this->damage;
}

int DoubleAxe::getWeight() const {
    return this->weight;
}
