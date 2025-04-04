#include "combat.hpp"

Combat::Combat(Material mat):
    material(mat), durability(mat)
{}

Combat::~Combat(){
    // Virtual destructor implementation (can be empty)
}

string Combat::getMaterial() const {
    switch (this->material) {
        case WOOD: return "Wooden";
        case STONE: return "Stone";
        case IRON: return "Iron";
        case GOLD: return "Gold";
        case DIAMOND: return "Diamond";
        default: return "Mysterious";
    }
}

string Combat::getName() const {
    return this->name;
}

bool Combat::isCombat() const {
    return true;
}

int Combat::getDurability() const {
    return this->durability;
}

void Combat::repair(int amount){
    this->durability += amount;
    if (this->durability > this->material) {
        this->durability = this->material;
    }
}

void Combat::loseDurability(int amount){
    this->durability -= amount;
    if (this->durability < 0) {
        this->durability = 0;
    }
}

void Combat::use() {
    if (this->durability <= 0) {
        cout << "Weapon is broken!" << endl;
        return;
    }
    this->durability--;
    if (this->durability == 0) {
        cout << "Weapon broke!" << endl;
    }
}
