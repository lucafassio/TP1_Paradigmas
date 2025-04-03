#include "necromancer.hpp"

Necromancer::Necromancer(const string& name)
    : Mage(name) {
}

void Necromancer::castSpell(const string& spellName) {
    if (mana <= 0) {
        cout << "Not enough mana!" << endl;
        return;
    }
    cout << name << " casts necromantic spell: " << spellName << "!" << endl;
    mana--;
}

void Necromancer::raiseDead(const string& corpseName) {
    if (mana >= 25) {
        cout << name << " raises " << corpseName << " from the dead!" << endl;
        mana -= 25;
    }
}

void Necromancer::strengthenControl() {
    magicPower += 5;
    cout << name << "'s control over the undead strengthens!" << endl;
}

void Necromancer::summonUndead() {
    if (mana >= 20) {
        cout << name << " summons undead minions!" << endl;
        mana -= 20;
    }
}

void Necromancer::curseEnemy() {
    if (mana >= 15) {
        cout << name << " places a death curse!" << endl;
        mana -= 15;
    }
}
