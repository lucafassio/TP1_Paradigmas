#include "spellbook.hpp"
#include <algorithm>

Spellbook::Spellbook(string name, int magicPower, int durability)
    : Magic(name, magicPower, durability) {
}

int Spellbook::getWeight() const {
    return 5 + spells.size();
}

void Spellbook::use() {
    if (durability <= 0) {
        cout << "Spellbook is damaged!" << endl;
        return;
    }
    durability--;
}

void Spellbook::castSpell(const string& spellName) {
    if (!hasSpell(spellName)) {
        cout << "Spell not found in book!" << endl;
        return;
    }
    if (durability <= 0) {
        cout << "Spellbook is damaged!" << endl;
        return;
    }
    cout << "Casting " << spellName << " from " << name << endl;
    durability--;
}

void Spellbook::addSpell(const string& spellName) {
    if (!hasSpell(spellName)) {
        spells.push_back(spellName);
        cout << "Added spell: " << spellName << endl;
    }
}

void Spellbook::removeSpell(const string& spellName) {
    auto it = std::find(spells.begin(), spells.end(), spellName);
    if (it != spells.end()) {
        spells.erase(it);
        cout << "Removed spell: " << spellName << endl;
    }
}

vector<string> Spellbook::listSpells() const {
    return spells;
}

bool Spellbook::hasSpell(const string& spellName) const {
    return std::find(spells.begin(), spells.end(), spellName) != spells.end();
}

int Spellbook::attack() {
    if (durability <= 0) {
        return 0;
    }
    return magicPower + spells.size();
}