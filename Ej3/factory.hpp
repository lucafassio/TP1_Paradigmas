#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// Combat weapons and base
#include "../Ej2/weapons/combat_weapons/combat.hpp"
#include "../Ej2/weapons/combat_weapons/sword/sword.hpp"
#include "../Ej2/weapons/combat_weapons/axe/axe.hpp"
#include "../Ej2/weapons/combat_weapons/spear/spear.hpp"
#include "../Ej2/weapons/combat_weapons/basto/basto.hpp"
#include "../Ej2/weapons/combat_weapons/double_axe/double_axe.hpp"

// Magic items
#include "../Ej2/weapons/magic_items/magic.hpp"
#include "../Ej2/weapons/magic_items/amulet/amulet.hpp"
#include "../Ej2/weapons/magic_items/potion/potion.hpp"
#include "../Ej2/weapons/magic_items/spellbook/spellbook.hpp"
#include "../Ej2/weapons/magic_items/staff/staff.hpp"

// Characters
#include "../Ej2/characters/character.hpp"

// Warriors
#include "../Ej2/characters/warriors/warrior.hpp"
#include "../Ej2/characters/warriors/barbarian/barbarian.hpp"
#include "../Ej2/characters/warriors/gladiator/gladiator.hpp"
#include "../Ej2/characters/warriors/knight/knight.hpp"
#include "../Ej2/characters/warriors/paladin/paladin.hpp"
#include "../Ej2/characters/warriors/mercenary/mercenary.hpp"

// Mages
#include "../Ej2/characters/mages/conjurer/conjurer.hpp"
#include "../Ej2/characters/mages/sorcerer/sorcerer.hpp"
#include "../Ej2/characters/mages/warlock/warlock.hpp"
#include "../Ej2/characters/mages/necromancer/necromancer.hpp"
#include "team.hpp"

#include <iostream>

enum WeaponType{
    //combat weapons
    AXE,
    BASTO,
    DOUBLE_AXE,
    SPEAR,
    SWORD,

    //magic items
    AMULET,
    POTION,
    SPELLBOOK,
    STAFF
};

class PersonajeFactory{
    private:

    public:
        PersonajeFactory();
        ~PersonajeFactory();  // Add destructor

        void createCharacter(Team* team, CharacterType type, string name);
        Weapon* createWeapon(WeaponType type, Material mat);
        Weapon* createWeapon(WeaponType type, AmuletProp prop);
        void addWeaponToCharacter(Character* character, Weapon* weapon);
};

#endif // FACTORY_HPP