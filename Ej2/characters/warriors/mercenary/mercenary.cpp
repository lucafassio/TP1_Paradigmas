#include "mercenary.hpp"

Mercenary::Mercenary(string name): 
    Warrior(name, MERCENARY), combatSkill(50) 
{}

void Mercenary::executeContract(const string& contractDetails) {
    cout << "Mercenary executes contract: " << contractDetails << endl;
    combatSkill += 5;
}

int Mercenary::getCombatSkill() const {
    return combatSkill;
}

void Mercenary::train() {
    combatSkill += 10;
    cout << "Mercenary trains. New combat skill: " << combatSkill << endl;
}
