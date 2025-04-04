#include "spellbook.hpp"

Spellbook::Spellbook(string name, int durability):
    Magic(durability), name(name){
        spells = {"Fireball", "Lightning Bolt", "Ice Spike", "Healing Light"};
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