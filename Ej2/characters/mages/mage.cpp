#include "mage.hpp"

Mage::Mage(string name)
    : name(name), health(100), mana(100), magicPower(50), spellSlots(3) {
}

string Mage::getName() const {
    return name;
}

int Mage::getHealth() const {
    return health;
}

int Mage::getMana() const {
    return mana;
}

int Mage::getBuff() const {
    return magicPower;
}

void Mage::reciveDamage(int dam) {
    health -= dam;
}

void Mage::addWeapon(Weapon* w) {
    if (weapons.first == nullptr) {
        weapons.first = w;
    } else if (weapons.second == nullptr) {
        weapons.second = w;
    }
    // If both slots are full, the weapon is not added
}

pair<Weapon*, Weapon*> Mage::inventory() const {
    return weapons;
}

int Mage::useWeapon(Weapon* w, Character* op) {
    if (!w) return 0; // No weapon to use
    if (w->isCombat()) {
        int fullDamage = magicPower + w->attack();
        op->reciveDamage(fullDamage);
        return fullDamage;
    }
    return 0; // Non-combat weapon, no damage dealt
}

int Mage::getMagicPower() const {
    return magicPower;
}

int Mage::getSpellSlots() const {
    return spellSlots;
}
