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
#include <fstream>
using namespace std;

//enums data
#include "../utils/enums_data.hpp"

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

//no me gustaba el nombre PersonajeFactory, lo cambie a Factory porque tambien hace armas.
class Factory{
    private:
        Factory() = delete;

    public:
        static shared_ptr<Character> createCharacter(CharacterType type, string name);
        static void addCharacterToTeam(shared_ptr<Team> team, shared_ptr<Character> character);
        static shared_ptr<Weapon> createWeapon(WeaponType type, Material mat);
        static shared_ptr<Weapon> createWeapon(WeaponType type, AmuletProp prop);
        static void addWeaponToCharacter(shared_ptr<Character> character, shared_ptr<Weapon> weapon);
};

#endif // FACTORY_HPP