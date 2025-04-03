#include "staff.hpp"

Staff::Staff(const string& name, int magicPower, int durability)
    : Magic(name, magicPower, durability) {
}

int Staff::getWeight() const {
    return magicPower * 2;
}

void Staff::use() {
    if (durability <= 0) {
        cout << "Staff is broken!" << endl;
        return;
    }
    durability--;
}

void Staff::castSpell(const string& spellName) {
    if (durability <= 0) {
        cout << "Staff is broken!" << endl;
        return;
    }
    cout << "Casting " << spellName << " with " << name << endl;
    durability--;
}

void Staff::recharge() {
    magicPower += 10;
    cout << "Staff recharged. New magic power: " << magicPower << endl;
}

void Staff::breakStaff() {
    durability = 0;
    cout << "Staff has been broken!" << endl;
}

int Staff::attack() {
    if (durability <= 0) {
        return 0;
    }
    return magicPower;
}