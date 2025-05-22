#include "../headers/factory.hpp"

shared_ptr<Character> Factory::createCharacter(CharacterType type, string name){
    switch (type){
        case BARBARIAN: return make_shared<Barbarian>(name);
        case GLADIATOR: return make_shared<Gladiator>(name);
        case KNIGHT: return make_shared<Knight>(name);
        case MERCENARY: return make_shared<Mercenary>(name, nullptr);
        case PALADIN: return make_shared<Paladin>(name);
        case CONJURER: return make_shared<Conjurer>(name);
        case NECRO: return make_shared<Necromancer>(name);
        case SORCERER: return make_shared<Sorcerer>(name);
        case WARLOCK: return make_shared<Warlock>(name);
        default: return nullptr;
    }
}

void Factory::addCharacterToTeam(shared_ptr<Team> team, shared_ptr<Character> character){
    if (team && character){
        team->members.push_back(character);
        cout << character->getName() << " has joined the team!" << endl;
        if (character->getType() == "Mercenary"){
            auto mercenary = dynamic_pointer_cast<Mercenary>(character);
            if (mercenary) mercenary->entersTeam(team);
        }
    } else {
        cout << "Error adding character to team!" << endl;
    }
}

shared_ptr<Weapon> Factory::createWeapon(WeaponType type, Material mat){
    switch (type){
        case AXE: return make_shared<Axe>(mat);
        case BASTO: return make_shared<Basto>(mat);
        case DOUBLE_AXE: return make_shared<DoubleAxe>(mat);
        case SPEAR: return make_shared<Spear>(mat);
        case SWORD: return make_shared<Sword>(mat);
        case AMULET: return make_shared<Amulet>(PROP_HEALING, nullptr);
        case POTION: return make_shared<Potion>("Health", 3);
        case SPELLBOOK: return make_shared<Spellbook>("Spellbook", 3);
        case STAFF: return make_shared<Staff>("Magic Staff", 3);
        default: return nullptr;
    }
}

shared_ptr<Weapon> Factory::createWeapon(WeaponType type, AmuletProp prop){
    if (type != AMULET) {
        cout << "Invalid weapon type for amulet creation!" << endl;
        return nullptr;
    }
    return make_shared<Amulet>(prop, nullptr);
}

void Factory::addWeaponToCharacter(shared_ptr<Character> character, shared_ptr<Weapon> weapon) {
    if (character && weapon){
        character->addWeapon(weapon);

        //si el arma es un amuleto, se le asigna el holder.
        shared_ptr<Amulet> amulet = dynamic_pointer_cast<Amulet>(weapon);
        if (amulet) {
            amulet->setHolder(character);
        }
    } 
    else cout << "Error adding weapon to character!" << endl;
}