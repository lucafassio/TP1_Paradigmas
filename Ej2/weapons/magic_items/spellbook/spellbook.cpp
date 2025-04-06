#include "spellbook.hpp"

Spellbook::Spellbook(string name, int durability):
    Magic(durability){
        spells = {"Fireball", "Lightning Bolt", "Ice Spike", "Healing Light"};
        this->name = name;
}

string Spellbook::getMaterial() const {
    return name;
}

void Spellbook::use() {
    cout << "Using " << name << "!" << endl;
    for (const string& spell : spells) {
        cout << "Casting " << spell << "!" << endl;
    }
}