#include "sorcerer.hpp"

Sorcerer::Sorcerer(const string& name)
    : Mage(name) {
}

void Sorcerer::castSpell(const string& spellName) {
    if (mana <= 0) {
        cout << "Not enough mana!" << endl;
        return;
    }
    cout << name << " casts " << spellName << " with enhanced power!" << endl;
    mana--;
}

void Sorcerer::summonFamiliar() {
    if (mana >= 10) {
        cout << name << " summons a magical familiar!" << endl;
        mana -= 10;
    }
}

void Sorcerer::teleport() {
    if (mana >= 20) {
        cout << name << " teleports in a flash of light!" << endl;
        mana -= 20;
    }
}

void Sorcerer::enhanceSpell() {
    magicPower += 5;
    cout << name << "'s spells are now more powerful!" << endl;
}

void Sorcerer::dispelMagic() {
    if (mana >= 15) {
        cout << name << " dispels magical effects!" << endl;
        mana -= 15;
    }
}
