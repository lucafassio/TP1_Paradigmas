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
    POISON,
    STUN,
    LUCK,
    IMMUNITY,
    INVISIBILITY
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

#endif // ENUMS_DATA_HPP