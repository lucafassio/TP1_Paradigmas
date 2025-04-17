#include "combat.hpp"

Combat::Combat(Material mat):
    material(mat), durability(mat)
{}

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

string Combat::use(shared_ptr<Team>, shared_ptr<Character>, shared_ptr<Character>, int) {
    return "no che, las armas de combate no usan esto (usan attack)";
}