#include "magic.hpp"

Magic::Magic(const string& name, int magicPower, int durability)
    : name(name), magicPower(magicPower), durability(durability) {
}

string Magic::getMaterial() const {
    return "Magic";
}

string Magic::getName() const {
    return name;
}



bool Magic::isCombat() const {
    return false;
}

int Magic::getMagicPower() const {
    return magicPower;
}

void Magic::enhanceMagicPower(int amount) {
    magicPower += amount;
    cout << name << "'s magic power enhanced to " << magicPower << endl;
}

void Magic::drainMagicPower(int amount) {
    magicPower = max(0, magicPower - amount);
    cout << name << "'s magic power drained to " << magicPower << endl;
}
