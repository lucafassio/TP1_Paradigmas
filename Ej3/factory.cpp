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
        case MERCENARY: team->members.push_back(new Mercenary(name, team)); break;
        case PALADIN: team->members.push_back(new Paladin(name)); break;
        default: break;
    }
    if (!team->members.back()) {
        cout << "Error creating character!" << endl;
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
        case AMULET: return new Amulet(PROP_HEALING, nullptr);
        case POTION: return new Potion("Health Potion", 3);
        case SPELLBOOK: return new Spellbook("Spellbook", 3);
        case STAFF: return new Staff("Magic Staff", 3);
        default: return nullptr;
    }
}

Weapon* PersonajeFactory::createWeapon(WeaponType type, AmuletProp prop){
    if (type != AMULET) {
        cout << "Invalid weapon type for amulet creation!" << endl;
        return nullptr;
    }
    return new Amulet(prop, nullptr);
}

void PersonajeFactory::addWeaponToCharacter(Character* character, Weapon* weapon) {
    if (character && weapon){
        character->addWeapon(weapon);

        //si el arma es un amuleto, se le asigna el holder.
        Amulet* amulet = dynamic_cast<Amulet*>(weapon);
        if (amulet) amulet->setHolder(character);
    } 
    else cout << "Error adding weapon to character!" << endl;
}