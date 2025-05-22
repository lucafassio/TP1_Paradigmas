#include "../headers/factory.hpp"

#include "../Ej2/characters/mages/headers/conjurer.hpp"
#include "../Ej2/characters/mages/headers/necromancer.hpp"
#include "../Ej2/characters/mages/headers/sorcerer.hpp"
#include "../Ej2/characters/mages/headers/warlock.hpp"

#include "../Ej2/characters/warriors/headers/barbarian.hpp"
#include "../Ej2/characters/warriors/headers/gladiator.hpp"
#include "../Ej2/characters/warriors/headers/knight.hpp"
#include "../Ej2/characters/warriors/headers/mercenary.hpp"
#include "../Ej2/characters/warriors/headers/paladin.hpp"

#include "../Ej2/weapons/magic_items/headers/amulet.hpp"
#include "../Ej2/weapons/magic_items/headers/potion.hpp"
#include "../Ej2/weapons/magic_items/headers/spellbook.hpp"
#include "../Ej2/weapons/magic_items/headers/staff.hpp"

#include "../Ej2/weapons/combat_weapons/headers/axe.hpp"
#include "../Ej2/weapons/combat_weapons/headers/basto.hpp"
#include "../Ej2/weapons/combat_weapons/headers/double_axe.hpp"
#include "../Ej2/weapons/combat_weapons/headers/spear.hpp"
#include "../Ej2/weapons/combat_weapons/headers/sword.hpp"


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

void Factory::createAndAddWeaponToCharacter(shared_ptr<Character> character, WeaponType type, Material mat) {
    if (!character) {
        cout << "Error: Character is null!" << endl;
        return;
    }

    shared_ptr<Weapon> weapon;
    switch (type) {
        case AXE: weapon = make_shared<Axe>(mat); break;
        case BASTO: weapon = make_shared<Basto>(mat); break;
        case DOUBLE_AXE: weapon = make_shared<DoubleAxe>(mat); break;
        case SPEAR: weapon = make_shared<Spear>(mat); break;
        case SWORD: weapon = make_shared<Sword>(mat); break;
        case SPELLBOOK: weapon = make_shared<Spellbook>("Spellbook"); break;
        case STAFF: weapon = make_shared<Staff>("Magic Staff"); break;
        default:
            cout << "Error: Invalid weapon type!" << endl;
            return;
    }

    character->addWeapon(weapon);
}

void Factory::createAndAddWeaponToCharacter(shared_ptr<Character> character, WeaponType type, AmuletProp prop) {
    if (!character) {
        cout << "Error: Character is null!" << endl;
        return;
    }

    if (type != AMULET) {
        cout << "Invalid weapon type for amulet creation!" << endl;
        return;
    }

    shared_ptr<Weapon> weapon = make_shared<Amulet>(prop);
    character->addWeapon(weapon);
}

void Factory::createAndAddWeaponToCharacter(shared_ptr<Character> character, WeaponType type, PotionType effect) {
    if (!character) {
        cout << "Error: Character is null!" << endl;
        return;
    }

    if (type != POTION) {
        cout << "Invalid weapon type for potion creation!" << endl;
        return;
    }
    shared_ptr<Weapon> weapon = make_shared<Potion>(effect);
    character->addWeapon(weapon);
}