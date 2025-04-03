#include "gladiator.hpp"

Gladiator::Gladiator(string name) : Warrior(name), popularity(0) {
    this->combatBuff = 5; // Gladiators start with a combat buff
}

void Gladiator::performMove(const string& moveName) {
    cout << name << " performs " << moveName << " to please the crowd!" << endl;
    increasePopularity();
}

int Gladiator::getPopularity() const {
    return popularity;
}

void Gladiator::increasePopularity() {
    popularity += 10;
    combatBuff += 2; // Popularity increases combat effectiveness
}