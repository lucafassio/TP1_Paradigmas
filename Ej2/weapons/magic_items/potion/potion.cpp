#include "potion.hpp"

Potion::Potion(const string& name, int magicPower, int durability, const string& type, bool expired)
    : Magic(name, magicPower, durability), type(type), expired(expired) {
}

int Potion::getWeight() const {
    return 1;
}

void Potion::use() {
    if (durability <= 0 || expired) {
        cout << "Potion cannot be used!" << endl;
        return;
    }
    durability--;
}

void Potion::castSpell(const string& spellName){
    cout << "Potions cannot cast spells!" << spellName << endl;
}

string Potion::getType() const {
    return type;
}

bool Potion::isExpired() const {
    return expired;
}

void Potion::increasePotency(int amount) {
    if (!expired) {
        magicPower += amount;
        cout << "Potion potency increased. New power: " << magicPower << endl;
    }
}

void Potion::decreasePotency(int amount) {
    if (!expired) {
        magicPower = max(0, magicPower - amount);
        cout << "Potion potency decreased. New power: " << magicPower << endl;
    }
}

int Potion::attack() {
    if (durability <= 0 || expired) {
        return 0;
    }
    return magicPower;
}