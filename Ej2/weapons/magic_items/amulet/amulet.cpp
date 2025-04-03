#include "amulet.hpp"

Amulet::Amulet(AmuletProp prop): 
    Magic(magicPower, durability), property(prop), active(false){
        name = getMaterial();
}

string Amulet::getMaterial() const {
    switch (property) {
        case HEALING: return "Healing Amulet";
        case FIRE: return "Fire Amulet";
        case INMUNITY: return "Inmunity Amulet";
        default: return "Unknown Amulet";
    }
}








int Amulet::getWeight() const {
    return 1;
}

void Amulet::use() {
    if (durability <= 0) {
        cout << "Amulet is broken!" << endl;
        return;
    }
    if (!active) {
        cout << "Amulet is not active!" << endl;
        return;
    }
    durability--;
}

void Amulet::castSpell(const string& spellName) {
    if (!active) {
        cout << "Amulet is not active!" << endl;
        return;
    }
    cout << "Casting " << spellName << " with property: " << property << endl;
}

void Amulet::activate() {
    active = true;
    cout << "Amulet activated!" << endl;
}

void Amulet::deactivate() {
    active = false;
    cout << "Amulet deactivated!" << endl;
}

string Amulet::getProperty() const {
    return property;
}

void Amulet::setProperty(const string& newProperty) {
    property = newProperty;
    cout << "Amulet property changed to: " << property << endl;
}

int Amulet::attack() {
    if (!active || durability <= 0) {
        return 0;
    }
    durability--;
    return magicPower;
}