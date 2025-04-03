#include "Ej2/weapons/weapon.hpp"

// Combat weapons and base
#include "Ej2/weapons/combat_weapons/combat.hpp"
#include "Ej2/weapons/combat_weapons/sword/sword.hpp"
#include "Ej2/weapons/combat_weapons/axe/axe.hpp"
#include "Ej2/weapons/combat_weapons/spear/spear.hpp"
#include "Ej2/weapons/combat_weapons/basto/basto.hpp"
#include "Ej2/weapons/combat_weapons/double_axe/double_axe.hpp"

// Magic items
#include "Ej2/weapons/magic_items/magic.hpp"
#include "Ej2/weapons/magic_items/amulet/amulet.hpp"
#include "Ej2/weapons/magic_items/potion/potion.hpp"
#include "Ej2/weapons/magic_items/spellbook/spellbook.hpp"
#include "Ej2/weapons/magic_items/staff/staff.hpp"

// Characters
#include "Ej2/characters/character.hpp"

// Warriors
#include "Ej2/characters/warriors/warrior.hpp"
#include "Ej2/characters/warriors/barbarian/barbarian.hpp"
#include "Ej2/characters/warriors/gladiator/gladiator.hpp"
#include "Ej2/characters/warriors/knight/knight.hpp"
#include "Ej2/characters/warriors/paladin/paladin.hpp"
#include "Ej2/characters/warriors/mercenary/mercenary.hpp"

// Mages
#include "Ej2/characters/mages/conjurer/conjurer.hpp"
#include "Ej2/characters/mages/sorcerer/sorcerer.hpp"
#include "Ej2/characters/mages/warlock/warlock.hpp"
#include "Ej2/characters/mages/necromancer/necromancer.hpp"

// Exercise 3
#include "Ej3/team.hpp"
#include "Ej3/factory.hpp"

int main(){
    Team* team1 = new Team(1);
    if (team1) cout << "Team 1 created correctly." << endl;
    Team* team2 = new Team(2);
    if (team2) cout << "Team 2 created correctly." << endl;
    PersonajeFactory* factory = new PersonajeFactory();
    if (factory) cout << "Factory created correctly." << endl;
    factory->createCharacter(team1, BARBARIAN, "Conan");
    if (team1->getMember("Conan")) cout << "Conan created correctly." << endl;
    factory->createCharacter(team2, BARBARIAN, "Maximus");
    if (team2->getMember("Maximus")) cout << "Maximus created correctly." << endl;

    cout << team1->getMember("Conan")->getName() << endl;
    cout << team1->getMember("Conan")->getHealth() << endl;
    cout << team2->getMember("Maximus")->getName() << endl;
    cout << team2->getMember("Maximus")->getHealth() << endl;

    team1->getMember("Conan")->useWeapon(nullptr, team2->getMember("Maximus"));
    cout << "Conan attacks Maximus!" << endl;
    cout << team2->getMember("Maximus")->getName() << endl;
    cout << team2->getMember("Maximus")->getHealth() << endl;
    
    Weapon* sword = factory->createWeapon(SWORD, IRON);
    if (sword) cout << "Sword created correctly." << endl;

    cout << "Attempting to use factory to add weapon..." << endl;
    factory->addWeaponToCharacter(team1->getMember("Conan"), sword);
    if (team1->getMember("Conan")->inventory().first) cout << "Sword added to Conan's inventory." << endl;
    cout << team1->getMember("Conan")->inventory().first->getName() << endl;
    cout << team1->getMember("Conan")->inventory().first->getMaterial() << endl;
    cout << team1->getMember("Conan")->inventory().first->attack() << endl;
    
    team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Maximus"));
    cout << "Conan attacks Maximus with sword!" << endl;
    cout << team2->getMember("Maximus")->getName() << endl;
    cout << team2->getMember("Maximus")->getHealth() << endl;
    
    return 0;
}