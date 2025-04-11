#ifndef ENUMS_DATA_HPP
#define ENUMS_DATA_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

//tipos de armas que pueden existir en el juego.
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

//tipos de personajes que pueden existir en el juego.
enum CharacterType{
    //guerreros
    BARBARIAN,
    GLADIATOR,
    KNIGHT,
    MERCENARY,
    PALADIN,

    //magos
    CONJURER,
    NECRO,
    SORCERER,
    WARLOCK
};

//nombre de cada efecto que puede tener un personaje.
enum Effect{
    REGENERATION,
    STRENGTH,
    BURNING,
    BLEEDING,
    POISON,
    STUN,
    LUCK,
    IMMUNITY,
    INVISIBILITY,
    FROZEN,
    STONE_SKIN,
    MAGIC_SILENCE,
    ELEMENTAL_EXPOSURE,
    MANA_LEECH,
    SOUL_LINKED
};

//materiales y durabilidad de las armas de combate.
enum Material{
    NONE = 0,
    WOOD = 59,
    STONE = 131,
    IRON = 250,
    GOLD = 32,
    DIAMOND = 1561
};

//propiedades de los amuletos (solo uno por amuleto).
enum AmuletProp{
    PROP_HEALING,
    PROP_STRENGTH,
    PROP_IMMUNITY,
    PROP_LUCK,
    PROP_INVISIBILITY
};

enum SorcererType {
    FIRE,
    WATER,
    AIR,
    EARTH
};

//ataques del ejercicio 4.
enum Attack{
    GOLPE_RAPIDO = 1,
    GOLPE_FUERTE = 2,
    DEFENSA_Y_GOLPE = 3
};

#endif // ENUMS_DATA_HPP