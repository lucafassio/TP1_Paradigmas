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

#include <memory>
#include <ctime>

int main(){
    srand(static_cast<unsigned>(time(nullptr)));
    cout << "========== Ej1: Characters ==========" << endl;
    auto team1 = make_shared<Team>("Team 1");
    if (team1) cout << "Team 1 created correctly." << endl;
    auto team2 = make_shared<Team>("Team 2");
    if (team2) cout << "Team 2 created correctly." << endl;

    shared_ptr<Character> conan = Factory::createCharacter(BARBARIAN, "Conan");
    Factory::addCharacterToTeam(team1, conan);
    shared_ptr<Character> maximus = Factory::createCharacter(BARBARIAN, "Maximus");
    Factory::addCharacterToTeam(team2, maximus);


    cout << endl << "========== Attack test ==========" << endl;

    cout << "Conan health: " << team1->getMember("Conan")->getHealth() << endl;
    cout << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;

    team1->getMember("Conan")->useWeapon(nullptr, team2->getMember("Maximus"), team2);

    cout << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;


    cout << endl << "========== Attack with weapon test ==========" << endl;
    
    cout << "Creating sword for Conan..." << endl;
    shared_ptr<Weapon> sword = Factory::createWeapon(SWORD, IRON);
    Factory::addWeaponToCharacter(team1->getMember("Conan"), sword);

    cout << endl << "Conan inventory: " << endl;
    if (team1->getMember("Conan")->inventory().first) cout << team1->getMember("Conan")->inventory().first->getName() << endl;
    if (team1->getMember("Conan")->inventory().second) cout << team1->getMember("Conan")->inventory().second->getName() << endl;

    cout << endl << "Sword stats: " << endl;
    cout << "Material: " << team1->getMember("Conan")->inventory().first->getMaterial() << endl;
    cout << "Damage: " << team1->getMember("Conan")->inventory().first->attack() << endl;
    cout << "Durability: " << team1->getMember("Conan")->inventory().first->getDurability() << endl;

    cout << endl << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;
    
    team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Maximus"), team2);

    cout << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;

    cout << endl << "Conans sword durability: " << team1->getMember("Conan")->inventory().first->getDurability() << endl;


    cout << endl << "========== Amulet test ==========" << endl;

    cout << "Creating amulet for Maximus..." << endl;
    shared_ptr<Weapon> amulet = Factory::createWeapon(AMULET, PROP_HEALING);
    Factory::addWeaponToCharacter(team2->getMember("Maximus"), amulet);

    cout << endl << "Sword stats: " << endl;
    cout << "Material: " << team1->getMember("Conan")->inventory().first->getMaterial() << endl;
    cout << "Damage: " << team1->getMember("Conan")->inventory().first->attack() << endl;
    cout << "Durability: " << team1->getMember("Conan")->inventory().first->getDurability() << endl;

    cout << endl << "Maximus inventory: " << endl;
    if (team2->getMember("Maximus")->inventory().first) cout << team2->getMember("Maximus")->inventory().first->getName() << endl;
    if (team2->getMember("Maximus")->inventory().second) cout << team2->getMember("Maximus")->inventory().second->getName() << endl;

    cout << endl << "Amulet stats: " << endl;
    cout << "Type: " << team2->getMember("Maximus")->inventory().first->getMaterial() << endl;
    cout << "Durability: " << team2->getMember("Maximus")->inventory().first->getDurability() << endl;
    
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;
    cout << "Simulating turn passed..." << endl;
    team2->getMember("Maximus")->effectUpdate();
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;


    cout << endl << "========== Mercenary betraying test ==========" << endl;

    Factory::addCharacterToTeam(team1, Factory::createCharacter(MERCENARY, "Alfredo"));
    Factory::addCharacterToTeam(team2, Factory::createCharacter(MERCENARY, "Carlos"));

    cout << endl;
    team1->showMembers();
    cout << endl;
    team2->showMembers();
    cout << endl;

    cout << "Carlos current health: " << team2->getMember("Carlos")->getHealth() << endl;

    team1->getMember("Alfredo")->useWeapon(nullptr, team2->getMember("Carlos"), team2);
    cout << endl << "Carlos health: " << team2->getMember("Carlos")->getHealth() << endl;

    auto carlos = dynamic_pointer_cast<Mercenary>(team2->getMember("Carlos"));
    carlos->betray(team2, team1);
    cout << "Carlos is now in Team 1." << endl;

    cout << endl;
    team1->showMembers();
    cout << endl;
    team2->showMembers();
    cout << endl;

    cout << "Carlos current health: " << team1->getMember("Carlos")->getHealth() << endl;


    cout << endl << "========== Mercenary stealing test ==========" << endl;

    cout << endl << "Carlos inventory: " << endl;
    if (carlos->inventory().first) cout << carlos->inventory().first->getName() << endl;
    if (carlos->inventory().second) cout << carlos->inventory().second->getName() << endl;

    cout << endl << "Alfredo inventory: " << endl;
    if (team1->getMember("Alfredo")->inventory().first) cout << team1->getMember("Alfredo")->inventory().first->getName() << endl;
    if (team1->getMember("Alfredo")->inventory().second) cout << team1->getMember("Alfredo")->inventory().second->getName() << endl;

    cout << endl << "Conan inventory: " << endl;
    if (team1->getMember("Conan")->inventory().first) cout << team1->getMember("Conan")->inventory().first->getName() << endl;
    if (team1->getMember("Conan")->inventory().second) cout << team1->getMember("Conan")->inventory().second->getName() << endl;

    cout << endl << "Carlos will try to steal a weapon from Alfredo and Conan." << endl;
    carlos->stealWeapon(team1->getMember("Alfredo")); //alfredo no tiene armas.
    carlos->stealWeapon(team1->getMember("Conan")); //conan tiene una espada.

    cout << endl << "Carlos inventory: " << endl;
    if (carlos->inventory().first) cout << carlos->inventory().first->getName() << endl;
    if (carlos->inventory().second) cout << carlos->inventory().second->getName() << endl;

    cout << endl << "Alfredo inventory: " << endl;
    if (team1->getMember("Alfredo")->inventory().first) cout << team1->getMember("Alfredo")->inventory().first->getName() << endl;
    if (team1->getMember("Alfredo")->inventory().second) cout << team1->getMember("Alfredo")->inventory().second->getName() << endl;

    cout << endl << "Conan inventory: " << endl;
    if (team1->getMember("Conan")->inventory().first) cout << team1->getMember("Conan")->inventory().first->getName() << endl;
    if (team1->getMember("Conan")->inventory().second) cout << team1->getMember("Conan")->inventory().second->getName() << endl;


    cout << endl << "========== Recruitment test ==========" << endl;
    cout << "Carlos will recruit an ally." << endl;
    carlos->recruitAlly();

    cout << endl;
    team1->showMembers();
    cout << endl;


    cout << endl << "========== Mercenary run away test ==========" << endl;
    cout << "Carlos will run away." << endl;
    carlos->runAway();

    cout << endl;
    team1->showMembers();
    cout << endl;

    cout << endl << "========== Necromancer raising tests ==========" << endl;
    Factory::addCharacterToTeam(team1, Factory::createCharacter(NECRO, "Velkor"));
    
    auto necro = dynamic_pointer_cast<Necromancer>(team1->getMember("Velkor"));
    necro->raiseDead(team1);

    cout << endl;
    team1->showMembers();
    cout << endl;

    cout << "Larry current health: " << team1->getMember("Larry")->getHealth() << endl;
    
    team1->getMember("Larry")->useWeapon(nullptr, team2->getMember("Maximus"), team2);

    cout << endl;
    team1->showMembers();
    cout << endl;


    cout << endl << "========== Necromancer draining tests ==========" << endl;
    cout << "Velkor will drain life from Maximus with max health." << endl;
    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;

    necro->drainLife(team2->getMember("Maximus"), team2);

    cout << endl;
    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;
    cout << endl;

    cout << endl << "Taking damage to Velkor." << endl;
    cout << endl;
    necro->receiveDamage(50);

    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;

    necro->drainLife(team2->getMember("Maximus"), team2);

    cout << endl;
    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;
    cout << endl;

    cout << endl << "========== Adam Warlock soul link tests ==========" << endl;
    shared_ptr<Character> adam = Factory::createCharacter(WARLOCK, "Adam");
    Factory::addCharacterToTeam(team1, adam);

    auto warlock = dynamic_pointer_cast<Warlock>(team1->getMember("Adam"));

    cout << endl;
    team1->showMembers();
    cout << endl;

    cout << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;

    cout << endl << "Adam will use soul link." << endl;
    warlock->soulLink(team1);

    cout << "Maximus will attack Conan with an axe." << endl;
    Factory::addWeaponToCharacter(team2->getMember("Maximus"), Factory::createWeapon(AXE, IRON));
    cout << endl;
    team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Conan"), team1);

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;
    
    
    cout << endl << "========== Killing test ==========" << endl;

    cout << "Larry's life will be reduce to 1." << endl;
    team1->getMember("Larry")->receiveDamage(team1->getMember("Larry")->getHealth() - 1);
    cout << "Larry current health: " << team1->getMember("Larry")->getHealth() << endl;

    cout << endl << "Maximus will kill Larry by hitting Adam." << endl;
    team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Adam"), team1);

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;

    //se puede dar que el cambio no se vea porque se redondean los ints.
    //ej si hace 24 de daño, se repartira entre 5 pero 24/5 = 4.8, se redondea a 4.
    cout << endl << "Now that Larry is dead, his soul link is broken. Next attack will be divided among less people." << endl;

    cout << "Adam's life will be reduce to 1." << endl;
    warlock->receiveDamage(warlock->getHealth() - 1);
    cout << "Adam current health: " << team1->getMember("Adam")->getHealth() << endl;

    cout << endl << "Maximus will kill Adam by hitting Conan." << endl;
    team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Conan"), team1);

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;
    
    cout << endl << "Now that Adam is dead, the soul link is broken. Maximus attacks Conan again." << endl;
    team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Conan"), team1);

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;

    
    cout << endl << "========== Necro revival and Adam Warlock born again tests ==========" << endl;

    cout << "Velkor will revive Adam." << endl;
    necro->reviveTeammate(warlock);
    cout << "Adam current health: " << team1->getMember("Adam")->getHealth() << endl;

    cout << "Velkor and Conan will die to test the born again." << endl;
    team1->getMember("Velkor")->receiveDamage(team1->getMember("Velkor")->getHealth());
    team1->getMember("Conan")->receiveDamage(team1->getMember("Conan")->getHealth());

    cout << endl << "Adam will use born again. Because they are 3, they will get 33% HP." << endl;

    warlock->bornAgain(team1);

    cout << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;
    
    
    cout << endl << "========== Gladiator tests ==========" << endl;
    Factory::addCharacterToTeam(team2, Factory::createCharacter(GLADIATOR, "Spartacus"));

    cout << "Maximus will die to test the gladiator." << endl;
    team2->getMember("Maximus")->receiveDamage(team2->getMember("Maximus")->getHealth());

    cout << endl << "Spartacus is alone in the team. Blast of Glory is active." << endl;
    shared_ptr<Gladiator> gladiator = dynamic_pointer_cast<Gladiator>(team2->getMember("Spartacus"));

    team2->showMembers();
    cout << endl;

    gladiator->blastOfGlory(team2, team1);

    cout << "Conan will hit Sportacus with a sword." << endl;
    Factory::addWeaponToCharacter(team1->getMember("Conan"), Factory::createWeapon(DOUBLE_AXE, DIAMOND));
    team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Spartacus"), team2);

    cout << "Spartacus current health: " << team2->getMember("Spartacus")->getHealth() << endl;


    cout << endl << "========== Paladin tests ==========" << endl;
    Factory::addCharacterToTeam(team1, Factory::createCharacter(PALADIN, "Galahad"));
    auto paladin = dynamic_pointer_cast<Paladin>(team1->getMember("Galahad"));

    cout << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;

    cout << endl << "Galahad will cure Conan and Adam." << endl;
    paladin->healingTeam(team1->getMember("Conan"), team1->getMember("Adam"));

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;

    cout << endl << "Galahad will use his ultimate." << endl;
    paladin->divineShield();

    cout << "Spartacus will attack Galahad three times with a double axe." << endl;
    Factory::addWeaponToCharacter(team2->getMember("Spartacus"), Factory::createWeapon(DOUBLE_AXE, DIAMOND));
    for (int i = 0; i < 3; i++){
        team2->getMember("Spartacus")->useWeapon(team2->getMember("Spartacus")->inventory().first, team1->getMember("Galahad"), team1);
        cout << "Galahad current health: " << team1->getMember("Galahad")->getHealth() << endl;
    }

    cout << endl << "Galahad current health: " << team1->getMember("Galahad")->getHealth() << endl;

    cout << "========== Knight Iron Will test ==========" << endl;
    Factory::addCharacterToTeam(team2, Factory::createCharacter(KNIGHT, "Lancelot"));
    auto knight = dynamic_pointer_cast<Knight>(team2->getMember("Lancelot"));

    cout << "Lancelot stats: " << endl;
    cout << "Armor: " << knight->getArmor() << endl;
    cout << "Buff: " << knight->getBuff() << endl;

    cout << endl << "Lancelot will use Iron Will." << endl;
    knight->ironWill();

    cout << endl << "Lancelot stats: " << endl;
    cout << "Armor: " << knight->getArmor() << endl;
    cout << "Buff: " << knight->getBuff() << endl;





    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}