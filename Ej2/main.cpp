//interfaz de weapons
#include "weapons/weapon.hpp"

//abstracta combat y sus derivadas
#include "weapons/combat_weapons/combat.hpp"
#include "weapons/combat_weapons/sword/sword.hpp"
#include "weapons/combat_weapons/axe/axe.hpp"
#include "weapons/combat_weapons/spear/spear.hpp"
#include "weapons/combat_weapons/basto/basto.hpp"
#include "weapons/combat_weapons/double_axe/double_axe.hpp"

//abstracta magic y sus derivadas
#include "weapons/magic_items/magic.hpp"
#include "weapons/magic_items/amulet/amulet.hpp"
#include "weapons/magic_items/potion/potion.hpp"
#include "weapons/magic_items/spellbook/spellbook.hpp"
#include "weapons/magic_items/staff/staff.hpp"

//interfaz de personajes
#include "characters/character.hpp"

//abstracta warrior y sus derivadas
#include "characters/warriors/warrior.hpp"
#include "characters/warriors/barbarian/barbarian.hpp"
#include "characters/warriors/gladiator/gladiator.hpp"
#include "characters/warriors/knight/knight.hpp"
#include "characters/warriors/paladin/paladin.hpp"
#include "characters/warriors/mercenary/mercenary.hpp"

//abstracta mage y sus derivadas
#include "characters/mages/conjurer/conjurer.hpp"
#include "characters/mages/sorcerer/sorcerer.hpp"
#include "characters/mages/warlock/warlock.hpp"
#include "characters/mages/necromancer/necromancer.hpp"

//incluyo la clase team y factory del ej 3 para facilitar los tests
#include "../Ej3/team.hpp"
#include "../Ej3/factory.hpp"

#include "../utils/HUD/display.hpp"

int main(){
    srand(static_cast<unsigned>(time(nullptr)));
    cout << "==========  Characters ==========" << endl;
    shared_ptr<Team> team1 = make_shared<Team>("Team 1");
    if (team1) cout << "Team 1 created correctly." << endl;
    shared_ptr<Team> team2 = make_shared<Team>("Team 2");
    if (team2) cout << "Team 2 created correctly." << endl;

    shared_ptr<Character> conan = Factory::createCharacter(BARBARIAN, "Conan");
    Factory::addCharacterToTeam(team1, conan);
    shared_ptr<Character> maximus = Factory::createCharacter(BARBARIAN, "Maximus");
    Factory::addCharacterToTeam(team2, maximus);


    cout << endl << "========== Attack test ==========" << endl;

    cout << "Conan health: " << team1->getMember("Conan")->getHealth() << endl;
    cout << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;

    cout << team1->getMember("Conan")->useWeapon(nullptr, team2->getMember("Maximus"), team2);

    cout << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;

    cout << endl << "========== Attack with weapon test ==========" << endl;
    
    cout << "Creating sword for Conan..." << endl;
    Factory::createAndAddWeaponToCharacter(team1->getMember("Conan"), SWORD, IRON);

    cout << endl << "Conan inventory: " << endl;
    if (team1->getMember("Conan")->inventory().first) cout << team1->getMember("Conan")->inventory().first->getName() << endl;
    if (team1->getMember("Conan")->inventory().second) cout << team1->getMember("Conan")->inventory().second->getName() << endl;

    cout << endl << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;
    
    cout << team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Maximus"), team2);

    cout << "Maximus health: " << team2->getMember("Maximus")->getHealth() << endl;


    cout << endl << "========== Amulet test ==========" << endl;

    cout << "Creating amulet for Maximus..." << endl;
    Factory::createAndAddWeaponToCharacter(team2->getMember("Maximus"), AMULET, PROP_HEALING);

    cout << endl << "Maximus inventory: " << endl;
    if (team2->getMember("Maximus")->inventory().first) cout << team2->getMember("Maximus")->inventory().first->getName() << endl;
    if (team2->getMember("Maximus")->inventory().second) cout << team2->getMember("Maximus")->inventory().second->getName() << endl;

    cout << team2->getMember("Maximus")->inventory().first->use(nullptr, team2->getMember("Maximus"), nullptr, 0);

    cout << endl << "Amulet stats: " << endl;
    cout << "Type: " << team2->getMember("Maximus")->inventory().first->getName() << endl;
    
    cout << endl << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;
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

    cout << team1->getMember("Alfredo")->useWeapon(nullptr, team2->getMember("Carlos"), team2);
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
    // necro->raiseDead(team1);

    // cout << endl;
    // team1->showMembers();
    // cout << endl;

    // cout << "Larry current health: " << team1->getMember("Larry")->getHealth() << endl;
    
    // cout << team1->getMember("Larry")->useWeapon(nullptr, team2->getMember("Maximus"), team2);

    // cout << endl;
    // team1->showMembers();
    // cout << endl;


    cout << endl << "========== Necromancer draining tests ==========" << endl;
    cout << "Velkor will drain life from Maximus with max health." << endl;
    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;

    necro->drainLife(team2->getMember("Maximus"));

    cout << endl;
    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;
    cout << endl;

    cout << endl << "Taking damage to Velkor." << endl;
    cout << endl;
    necro->receiveDamage(50);

    cout << "Velkor current health: " << team1->getMember("Velkor")->getHealth() << endl;
    cout << "Maximus current health: " << team2->getMember("Maximus")->getHealth() << endl;

    necro->drainLife(team2->getMember("Maximus"));

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
    Factory::createAndAddWeaponToCharacter(team2->getMember("Maximus"), AXE, IRON);
    cout << endl;
    cout << team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Conan"), team1);

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;
    
    
    cout << endl << "========== Killing test ==========" << endl;

    cout << "Larry's life will be reduce to 1." << endl;
    team1->getMember("Larry")->receiveDamage(team1->getMember("Larry")->getHealth() - 1);
    cout << "Larry current health: " << team1->getMember("Larry")->getHealth() << endl;

    cout << endl << "Maximus will kill Larry by hitting Adam." << endl;
    cout << team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Adam"), team1);

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
    cout << team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Conan"), team1);

    cout << endl << "Everyone's current health: " << endl;
    for (auto& member : team1->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;
    
    cout << endl << "Now that Adam is dead, the soul link is broken. Maximus attacks Conan again." << endl;
    cout << team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Conan"), team1);

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

    cout << "Maximus will attack Galahad three times with an iron axe." << endl;
    for (int i = 0; i < 3; i++){
        cout << team2->getMember("Maximus")->useWeapon(team2->getMember("Maximus")->inventory().second, team1->getMember("Galahad"), team1);
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


    cout << "========== SpellBook tests ==========" << endl;
    
    Factory::addCharacterToTeam(team2, Factory::createCharacter(SORCERER, "Merlin"));
    Factory::createAndAddWeaponToCharacter(team2->getMember("Merlin"), SPELLBOOK, NONE);
    Factory::createAndAddWeaponToCharacter(team2->getMember("Maximus"), SPELLBOOK, NONE);

    cout << "Maximus will try to use the spellbook." << endl;
    cout << team2->getMember("Maximus")->inventory().first->use(team2, team2->getMember("Maximus"), team1->getMember("Conan"), 0);

    cout << endl << "Now Merlin will use the spellbook castin every spell." << endl;

    cout << "First lets see Merlins team" << endl;
    team2->showMembers();
    
    cout << endl << team2->getMember("Merlin")->inventory().first->use(team2, team2->getMember("Merlin"), team1->getMember("Conan"), 1);
    cout << team2->getMember("Merlin")->inventory().first->use(team2, team2->getMember("Merlin"), team1->getMember("Conan"), 2);
    cout << team2->getMember("Merlin")->inventory().first->use(team2, team2->getMember("Merlin"), team1->getMember("Conan"), 3);

    //este es el mana_leech, no tiene mucho sentido usarlo en Conan
    cout << team2->getMember("Merlin")->inventory().first->use(team2, team2->getMember("Merlin"), necro, 4);
    cout << team2->getMember("Merlin")->inventory().first->use(team2, team2->getMember("Merlin"), team1->getMember("Conan"), 5);

    cout << endl << "After cloning, Merlins team:" << endl;
    team2->showMembers();
    
    cout << "Conan current health: " << team1->getMember("Conan")->getHealth() << endl;
    cout << "Velkor current mana: " << necro->getMana() << endl;

    cout << "Simulating turn passed..." << endl;
    team1->getMember("Conan")->effectUpdate();
    necro->effectUpdate();

    cout << endl << "Conan current health: " << team1->getMember("Conan")->getHealth() << endl;
    cout << "Velkor current mana: " << necro->getMana() << endl;

    cout << endl << "Conan will try to take revenge." << endl;
    cout << team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Merlin"), team2);

    cout << "Simulating another turn..." << endl;
    team1->getMember("Conan")->effectUpdate();
    team1->getMember("Conan")->effectUpdate();
    team1->getMember("Conan")->effectUpdate();
    
    cout << endl << "Now that another turn passed, Conan can revenge himself." << endl;
    cout << team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Merlin"), team2);


    cout << endl << "========== Gladiator tests ==========" << endl;
    Factory::addCharacterToTeam(team2, Factory::createCharacter(GLADIATOR, "Spartacus"));

    cout << "Everyone in Spartacus team will die to test the gladiator." << endl;
    team2->getMember("Maximus")->receiveDamage(team2->getMember("Maximus")->getHealth());
    team2->getMember("Maximus")->receiveDamage(team2->getMember("Maximus")->getHealth());
    team2->getMember("Lancelot")->receiveDamage(100000); //no se me moria mas
    team2->getMember("Merlin")->receiveDamage(team2->getMember("Merlin")->getHealth());
    team2->getMember("Merlin's Clone")->receiveDamage(team2->getMember("Merlin's Clone")->getHealth());

    //en el caso de que veas que no se mueren es porque estan aguantando por la armadura, no es un bug.
    //todos los warriors tienen armadura y eso les baja el daño recibido.
    //para arreglarlo copia mas veces la linea de recibir daño o hace que reciban 1000 de daño o algo asi jeje

    cout << endl << "Spartacus is alone in the team. Blast of Glory is active." << endl;
    shared_ptr<Gladiator> gladiator = dynamic_pointer_cast<Gladiator>(team2->getMember("Spartacus"));

    //muestro la vida de todos
    for (auto& member : team2->getMembers())
        cout << member->getName() << ": " << member->getHealth() << endl;

    gladiator->blastOfGlory(team2, team1);

    cout << "Conan will hit Sportacus with a sword." << endl;
    Factory::createAndAddWeaponToCharacter(team1->getMember("Conan"), DOUBLE_AXE, DIAMOND);
    cout << team1->getMember("Conan")->useWeapon(team1->getMember("Conan")->inventory().first, team2->getMember("Spartacus"), team2);

    cout << "Spartacus current health: " << team2->getMember("Spartacus")->getHealth() << endl;

    //como dijeron que no hacia falta probar todos los personajes y todos sus metodos lo deje aca que es lo que
    //habia estado probando por mi cuenta para ver si andaba, no es lo mas prolijo que hay pero un poco trate de
    //acomodarlo. Tengan encuenta que son como mis notas de lo que fui probando jeje.
    
    return 0;
}