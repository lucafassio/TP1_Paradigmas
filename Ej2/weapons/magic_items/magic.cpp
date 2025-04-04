#include "magic.hpp"

Magic::Magic(int durability): 
    durability(durability)
{}

string Magic::getName() const {
    return name;
}

bool Magic::isCombat() const {
    return false;
}

int Magic::getDurability() const {
    return durability;
}

int Magic::attack(){
    cout << "Attacking with magic!" << endl;
    return 0; // Placeholder for magic attack damage
}