#include "factory.hpp"

PersonajeFactory::PersonajeFactory(){}

PersonajeFactory::~PersonajeFactory() {}

void PersonajeFactory::createCharacter(Team* team, CharacterType type, string name){
    switch (type){
        case CONJURER: team->members.push_back(new Conjurer(name)); break;
        case NECRO: team->members.push_back(new Necromancer(name)); break;
        case SORCERER: team->members.push_back(new Sorcerer(name)); break;
        case WARLOCK: team->members.push_back(new Warlock(name)); break;
        case BARBARIAN: team->members.push_back(new Barbarian(name)); break;
        case GLADIATOR: team->members.push_back(new Gladiator(name)); break;
        case KNIGHT: team->members.push_back(new Knight(name)); break;
        case MERCENARY: team->members.push_back(new Mercenary(name)); break;
        case PALADIN: team->members.push_back(new Paladin(name)); break;
        default: break;
    }
    if (!team->members.back()) {
        cout << "Error creating character!" << endl; //throw?
        return;
    }
}

Weapon* PersonajeFactory::createWeapon(WeaponType type, Material mat) {
    switch (type) {
        case AXE: return new Axe(mat);
        case BASTO: return new Basto();
        case DOUBLE_AXE: return new DoubleAxe(mat);
        case SPEAR: return new Spear(mat);
        case SWORD: return new Sword(mat);
        // case AMULET: return new Amulet("Magic Amulet");
        // case POTION: return new Potion("Health Potion");
        // case SPELLBOOK: return new Spellbook("Spellbook");
        case STAFF: return nullptr; // Implement if Staff class exists
        default: return nullptr;
    }
}

void PersonajeFactory::addWeaponToCharacter(Character* character, Weapon* weapon) {
    if (character && weapon){
        cout << character->getName() << " adds weapon: " << weapon->getName() << endl;
        character->addWeapon(weapon);
    } else {
        cout << "Error adding weapon to character!" << endl; //throw?
    }
}