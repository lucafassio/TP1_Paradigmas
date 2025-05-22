#include "../headers/sorcerer.hpp"

Sorcerer::Sorcerer(string name):
    Mage(name, SORCERER, 100, 100), currentType(FIRE)
{}

string Sorcerer::useWeapon(unique_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) {
    string logText;
    int finalDamage = BASE_DAMAGE;

    logText += name + " (Sorcerer) attacks " + target->getName() + " (" + target->getType() + ")";

    if (weapon) {
        if (weapon->isCombat()) finalDamage += weapon->attack();
        logText += " with " + weapon->getName();
    } else {
        logText += " with his own power";
    }

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde.
    if (hasEffect(SCARED) && rand() % 100 < 60) {
        logText += ". " + name + " (Sorcerer) is scared and misses the attack!\n";
        return logText;
    }

    if (stunned) {
        logText += ". " + name + " (Sorcerer) is stunned!\n";
        stunned = false;
        return logText;
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (forcedCritical) {
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //reparto el daño para cuando el warlock haga Soul Link.
    logText += Mage::warlockSoulLink(target, targetTeam, finalDamage);

    if ((target->getType() == "Barbarian" || target->getType() == "Gladiator") && rand() % 100 < 20 && target->getHealth()) {
        //los barbaros y gladiadores tienen un 20% de chance de contraatacar haciendo un 40% menos de daño.
        this->receiveDamage(finalDamage * 0.6);
        logText += target->getName() + " (" + target->getType() + ") counterattacks!\n";
    }

    cout << logText; // Print the log at the end
    return logText;
}

void Sorcerer::elementalAttack(shared_ptr<Character> target) {
    switch (currentType) {
        case FIRE: target->applyEffect(BURNING, 2); break;
        case WATER: target->applyEffect(FREEZING, 1); break;
        case AIR: target->applyEffect(STUN, 1); break;
        case EARTH: target->applyEffect(STONE_SKIN, 2); break;
    }
}

void Sorcerer::changeElement(SorcererType newType){
    currentType = newType;
}

string Sorcerer::getType() const {
    switch (currentType) {
        case FIRE: return "Fire Sorcerer";
        case WATER: return "Water Sorcerer";
        case AIR: return "Air Sorcerer";
        case EARTH: return "Earth Sorcerer";
    }
    return "Unknown Sorcerer";
}
