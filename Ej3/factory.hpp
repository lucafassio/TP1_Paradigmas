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
#include "../utils/data.hpp"

// Combat weapons and base
#include "../Ej2/weapons/combat_weapons/sword/sword.hpp"
#include "../Ej2/weapons/combat_weapons/axe/axe.hpp"
#include "../Ej2/weapons/combat_weapons/spear/spear.hpp"
#include "../Ej2/weapons/combat_weapons/basto/basto.hpp"
#include "../Ej2/weapons/combat_weapons/double_axe/double_axe.hpp"

// Magic items
#include "../Ej2/weapons/magic_items/amulet/amulet.hpp"
#include "../Ej2/weapons/magic_items/potion/potion.hpp"
#include "../Ej2/weapons/magic_items/spellbook/spellbook.hpp"
#include "../Ej2/weapons/magic_items/staff/staff.hpp"

// Warriors
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
#include "../Ej2/characters/mages/necromancer/larry.hpp"

// Combat weapons and base
#include "../Ej2/weapons/combat_weapons/combat.cpp"
#include "../Ej2/weapons/combat_weapons/sword/sword.cpp"
#include "../Ej2/weapons/combat_weapons/axe/axe.cpp"
#include "../Ej2/weapons/combat_weapons/spear/spear.cpp"
#include "../Ej2/weapons/combat_weapons/basto/basto.cpp"
#include "../Ej2/weapons/combat_weapons/double_axe/double_axe.cpp"

// Magic items
#include "../Ej2/weapons/magic_items/magic.cpp"
#include "../Ej2/weapons/magic_items/amulet/amulet.cpp"
#include "../Ej2/weapons/magic_items/potion/potion.cpp"
#include "../Ej2/weapons/magic_items/spellbook/spellbook.cpp"
#include "../Ej2/weapons/magic_items/staff/staff.cpp"

// Warriors
#include "../Ej2/characters/warriors/warrior.cpp"
#include "../Ej2/characters/warriors/barbarian/barbarian.cpp"
#include "../Ej2/characters/warriors/gladiator/gladiator.cpp"
#include "../Ej2/characters/warriors/knight/knight.cpp"
#include "../Ej2/characters/warriors/paladin/paladin.cpp"
#include "../Ej2/characters/warriors/mercenary/mercenary.cpp"

// Mages
#include "../Ej2/characters/mages/mage.cpp"
#include "../Ej2/characters/mages/conjurer/conjurer.cpp"
#include "../Ej2/characters/mages/sorcerer/sorcerer.cpp"
#include "../Ej2/characters/mages/warlock/warlock.cpp"
#include "../Ej2/characters/mages/necromancer/necromancer.cpp"
#include "../Ej2/characters/mages/necromancer/larry.cpp"

class Team;

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