#include "warlock.hpp"

Warlock::Warlock(string name)
    : Mage(name) {
}

void Warlock::castSpell(const string& spellName) {
    if (mana <= 0) {
        cout << "Not enough mana!" << endl;
        return;
    }
    cout << name << " casts dark spell: " << spellName << "!" << endl;
    mana--;
}

void Warlock::performRitual(const string& ritualName) {
    if (mana >= 30) {
        cout << name << " performs dark ritual: " << ritualName << "!" << endl;
        mana -= 30;
        magicPower += 10;
    }
}

int Warlock::getDarkEnergy() const {
    return magicPower * 2;
}

void Warlock::absorbDarkEnergy() {
    health -= 10;
    magicPower += 20;
    cout << name << " absorbs dark energy!" << endl;
}
