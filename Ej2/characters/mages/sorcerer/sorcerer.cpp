#include "sorcerer.hpp"

Sorcerer::Sorcerer(string name):
    Mage(name, SORCERER, 100), currentType(FIRE), cooldown(0), switchCooldown(0) {}

void Sorcerer::attack(shared_ptr<Character> target) {
    elementalAttack(target);
}

void Sorcerer::special(shared_ptr<Character> target, shared_ptr<Team> team) {
    if (!specialReady()) return;
    elementalSpecial(target, team);
    resetCooldown();
}

void Sorcerer::elementalAttack(shared_ptr<Character> target) {
    switch (currentType) {
        case FIRE: target->applyEffect(BURNING, 2); break;
        case WATER: target->applyEffect(FROZEN, 1); break;
        case AIR: target->applyEffect(STUN, 1); break;
        case EARTH: target->applyEffect(STONE_SKIN, 2); break;
    }
}

void Sorcerer::elementalSpecial(shared_ptr<Character> target, shared_ptr<Team> team) {
    switch (currentType) {
        case FIRE:
            target->applyEffect(ELEMENTAL_EXPOSURE, 3);
            break;
        case WATER:
            target->applyEffect(MAGIC_SILENCE, 2);
            break;
        case AIR:
            target->applyEffect(POISON, 3);
            break;
        case EARTH:
            for (const auto& c : team->getMembers()) {
                c->applyEffect(STONE_SKIN, 2);
            }
            break;
    }
}

void Sorcerer::changeElement(SorcererType newType) {
    if (canChangeElement()) {
        currentType = newType;
        switchCooldown = 1;
    }
}

bool Sorcerer::canChangeElement() const {
    return switchCooldown == 0;
}

void Sorcerer::resetCooldown() {
    cooldown = 3;
}

void Sorcerer::tickCooldown() {
    if (cooldown > 0) cooldown--;
    if (switchCooldown > 0) switchCooldown--;
}

bool Sorcerer::specialReady() const {
    return cooldown == 0;
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
