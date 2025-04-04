#include "potion.hpp"

Potion::Potion(string type, int durability): 
    Magic(durability), type(type), expired(false){
        name = type + " Potion";
}

string Potion::getMaterial() const {
    return name;
}

void Potion::use() {
    if (expired) {
        cout << "The potion is expired!" << endl;
        return;
    }
    cout << "Using " << name << "!" << endl;
    expired = true; // Potion can only be used once
}