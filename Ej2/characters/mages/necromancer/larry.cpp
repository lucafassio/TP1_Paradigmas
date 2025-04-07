#include "Larry.hpp"
#include "../../../../Ej3/team.hpp"

Larry::Larry():
    //pongo tipo necro pero no afecta en nada porque overrideo el metodo getType.
    Mage("Larry", NECRO, 0)
{}

string Larry::getType() const {
    return "Skelly";
}

//el skelly no tiene mana, no puede usar armas y no puede curarse.
int Larry::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = SKELETON_DAMAGE + Mage::useWeapon(weapon, target, targetTeam);

    cout << name << " (Skelly) attacks " << target->getName() << " (" << target->getType() << ")";

    //20% de probabilidad de activar un crítico (si ya venia forzado sigue igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (strengthBuff){
        finalDamage = static_cast<int>(finalDamage * 1.5); //aplico el buff de fuerza.
        
        //desactivo el buff de fuerza (si aun quedan turnos en el efecto luego se volvera a activar).
        strengthBuff = false; 
    }

    if (forcedCritical){
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //aplicar daño al oponente.
    target->receiveDamage(finalDamage);
    if (!target->getHealth()) targetTeam->loseMember(target);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

void Larry::loseLifetime(shared_ptr<Team> LarryTeam){
    lifetimeRemaining--;
    if (lifetimeRemaining == 0){
        LarryTeam->loseMember(shared_from_this());
        cout << "Larry has died!" << endl;
    }
}