#include "factory.hpp"

#include "../Ej2/characters/mages/conjurer/conjurer.hpp"
#include "../Ej2/characters/mages/necromancer/necromancer.hpp"
#include "../Ej2/characters/mages/sorcerer/sorcerer.hpp"
#include "../Ej2/characters/mages/warlock/warlock.hpp"

#include "../Ej2/characters/warriors/barbarian/barbarian.hpp"
#include "../Ej2/characters/warriors/gladiator/gladiator.hpp"
#include "../Ej2/characters/warriors/knight/knight.hpp"
#include "../Ej2/characters/warriors/mercenary/mercenary.hpp"
#include "../Ej2/characters/warriors/paladin/paladin.hpp"

#include "../Ej2/weapons/magic_items/amulet/amulet.hpp"
#include "../Ej2/weapons/magic_items/potion/potion.hpp"
#include "../Ej2/weapons/magic_items/spellbook/spellbook.hpp"
#include "../Ej2/weapons/magic_items/staff/staff.hpp"

#include "../Ej2/weapons/combat_weapons/axe/axe.hpp"
#include "../Ej2/weapons/combat_weapons/basto/basto.hpp"
#include "../Ej2/weapons/combat_weapons/double_axe/double_axe.hpp"
#include "../Ej2/weapons/combat_weapons/spear/spear.hpp"
#include "../Ej2/weapons/combat_weapons/sword/sword.hpp"


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

    unique_ptr<Weapon> weapon;
    switch (type) {
        case AXE: weapon = make_unique<Axe>(mat); break;
        case BASTO: weapon = make_unique<Basto>(mat); break;
        case DOUBLE_AXE: weapon = make_unique<DoubleAxe>(mat); break;
        case SPEAR: weapon = make_unique<Spear>(mat); break;
        case SWORD: weapon = make_unique<Sword>(mat); break;
        case SPELLBOOK: weapon = make_unique<Spellbook>("Spellbook"); break;
        case STAFF: weapon = make_unique<Staff>("Magic Staff"); break;
        default:
            cout << "Error: Invalid weapon type!" << endl;
            return;
    }

    character->addWeapon(move(weapon));
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

    unique_ptr<Weapon> weapon = make_unique<Amulet>(prop);
    character->addWeapon(move(weapon));
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
    unique_ptr<Weapon> weapon = make_unique<Potion>(effect);
    character->addWeapon(move(weapon));
}