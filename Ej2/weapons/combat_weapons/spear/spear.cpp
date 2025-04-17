#include "spear.hpp"

Spear::Spear(Material mat): 
    Combat(mat){
        setDamage(mat);
        name = this->getMaterial() + " Spear";
}

Spear::Spear(const Spear& other):
    Combat(other.material){
        this->durability = other.durability;
        this->damage = other.damage;
        this->length = other.length;
        this->name = other.name;
}

void Spear::setDamage(Material mat){
    switch (mat){
        case NONE: break;
        case WOOD: this->damage = 2; break;
        case STONE: this->damage = 3; break;
        case IRON: this->damage = 4; break;
        case GOLD: this->damage = 2; break;
        case DIAMOND: this->damage = 5; break;
    }
}

int Spear::attack(){
    if (this->durability <= 0){
        cout << "Spear is broken!" << endl;
        return 0;
    }
    if (this->durability == 1) cout << "Spear broke!" << endl;
    this->durability--;
    return this->damage;
}

int Spear::getDamage() const {
    return this->damage;
}

int Spear::getLength() const {
    return this->length;
}