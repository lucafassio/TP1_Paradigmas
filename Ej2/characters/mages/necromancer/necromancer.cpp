#include "necromancer.hpp"
#include "../../../../Ej3/team.hpp"

Necromancer::Necromancer(string name)
    : Mage(name, NECRO, 100, 100)
{}

int Necromancer::useWeapon(Weapon* weapon, Character* target, Team* targetTeam){
    int finalDamage = BASE_DAMAGE + Mage::useWeapon(weapon, target, targetTeam);

    cout << name << " (Necromancer) attacks " << target->getName() << " (" << target->getType() << ")";

    if(weapon) cout << " with " << weapon->getName();
    else cout << " with his own power";

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
    target->reciveDamage(finalDamage);
    if (!target->getHealth()) targetTeam->loseMember(target);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

void Necromancer::raiseDead(){
    if (skellyAlive) {
        cout << name << " already has Skelly alive!" << endl;
        return;
    }
    if (mana >= 25) {
        cout << name << " raises Skelly from the dead!" << endl;
        skellyAlive = true;
        mana -= 25;
    }
}
