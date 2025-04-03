#include "magic.hpp"

Magic::Magic(int magicPower, int durability): 
    magicPower(magicPower), durability(durability){
}

string Magic::getName() const {
    return name;
}

bool Magic::isCombat() const {
    return false;
}

int Magic::getDurability() const {
    return durability;
}
