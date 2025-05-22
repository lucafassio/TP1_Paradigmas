#ifndef FACTORY_HPP
#define FACTORY_HPP

//enums data
#include "../../utils/data.hpp"

#include "../../Ej2/characters/mages/headers/conjurer.hpp"
#include "../../Ej2/characters/mages/headers/necromancer.hpp"
#include "../../Ej2/characters/mages/headers/sorcerer.hpp"
#include "../../Ej2/characters/mages/headers/warlock.hpp"

#include "../../Ej2/characters/warriors/headers/barbarian.hpp"
#include "../../Ej2/characters/warriors/headers/gladiator.hpp"
#include "../../Ej2/characters/warriors/headers/knight.hpp"
#include "../../Ej2/characters/warriors/headers/mercenary.hpp"
#include "../../Ej2/characters/warriors/headers/paladin.hpp"

#include "../../Ej2/weapons/magic_items/headers/amulet.hpp"
#include "../../Ej2/weapons/magic_items/headers/potion.hpp"
#include "../../Ej2/weapons/magic_items/headers/spellbook.hpp"
#include "../../Ej2/weapons/magic_items/headers/staff.hpp"

#include "../../Ej2/weapons/combat_weapons/headers/axe.hpp"
#include "../../Ej2/weapons/combat_weapons/headers/basto.hpp"
#include "../../Ej2/weapons/combat_weapons/headers/double_axe.hpp"
#include "../../Ej2/weapons/combat_weapons/headers/spear.hpp"
#include "../../Ej2/weapons/combat_weapons/headers/sword.hpp"

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