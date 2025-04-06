#include "basto.hpp"

Basto::Basto(Material reinforcement) : 
    Combat(WOOD) {
        this->damage = 3;
        name = "hola";
        reinforce(reinforcement);
}

int Basto::attack(){
    if (this->durability <= 0) {
        cout << "Basto is broken!" << endl;
        return 0;
    }
    if (this->durabilityBoost) {
        if (this->durabilityBoost == 1) this->reinforce(NONE);
        this->durabilityBoost--;
        cout << "Basto is no longer reinforced!" << endl;
    }
    else {
        if (this->durability == 1) cout << "Basto broke!" << endl;
        this->durability--;
    }
    return this->getDamage();
}

void Basto::reinforce(Material mat) {
    switch (mat) {
        case NONE:
            this->damageBoost = 0;
            this->durabilityBoost = 0;
            name = "Basto";
            break;
        case WOOD: 
            this->damageBoost = 2;
            this->durabilityBoost = WOOD;
            name = "Reinforced Basto (wood)";
            break;
        case STONE:
            this->damageBoost = 3;
            this->durabilityBoost = STONE - WOOD;
            name = "Reinforced Basto (stone)";
            break;
        case IRON:
            this->damageBoost = 4;
            this->durabilityBoost = IRON - WOOD;
            name = "Reinforced Basto (iron)";
            break;
        case GOLD:
            this->damageBoost = 2;
            this->durabilityBoost = GOLD - WOOD;
            name = "Reinforced Basto (gold)";
            break;
        case DIAMOND:
            this->damageBoost = 5;
            this->durabilityBoost = DIAMOND - WOOD;
            name = "Reinforced Basto (diamond) ";
            break;
        default:
            cout << "Invalid material!" << endl;
            break;
    }
}

int Basto::getDamage() const {
    return this->damage + this->damageBoost;
}

void Basto::getReinforcement() const {
    switch (this->reinforcement) {
        case NONE: cout << "Basto is not reinforced." << endl; break;
        case WOOD: cout << "Basto is reinforced with wood." << endl; break;
        case STONE: cout << "Basto is reinforced with stone." << endl; break;
        case IRON: cout << "Basto is reinforced with iron." << endl; break;
        case GOLD: cout << "Basto is reinforced with gold." << endl; break;
        case DIAMOND: cout << "Basto is reinforced with diamond." << endl; break;
        default: cout << "Basto is not reinforced." << endl; break;
    }
}
