#include "conjurer.hpp"

Conjurer::Conjurer(const string& name)
    : Mage(name)
{}

void Conjurer::castSpell(const string& spellName) {
    if (mana <= 0) {
        cout << "Not enough mana!" << endl;
        return;
    }
    cout << name << " conjures spell: " << spellName << "!" << endl;
    mana--;
}

void Conjurer::summonCreature(const string& creatureName) {
    if (mana >= 20) {
        cout << name << " summons a " << creatureName << "!" << endl;
        mana -= 20;
    }
}

int Conjurer::getSummoningPower() const {
    return magicPower + spellSlots;
}

void Conjurer::enhanceSummoningPower() {
    magicPower += 10;
    cout << name << "'s summoning power increases!" << endl;
}
