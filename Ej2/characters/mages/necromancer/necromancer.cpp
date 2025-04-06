#include "necromancer.hpp"
#include "../../../../Ej3/team.hpp"
#include "larry.hpp"

Necromancer::Necromancer(string name): 
    Mage(name, NECRO, 100, 100)
{}

int Necromancer::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
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

void Necromancer::raiseDead(shared_ptr<Team> currentTeam){
    if (larryAlive){
        cout << name << " already has a Skelly alive!" << endl;
        return;
    }
    if (mana >= 25){
        cout << name << " raises Larry from the dead!" << endl;
        currentTeam->members.push_back(static_pointer_cast<Character>(make_shared<Larry>()));
        mana -= 25;
    }
}

void Necromancer::drainLife(shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    if (mana >= 10){
        cout << name << " drains 10 life from " << target->getName();
        target->reciveDamage(10);
        if (!target->getHealth()){
            targetTeam->loseMember(target);
            cout << " taking him to the death world";
        }
        cout << "!" << endl;
        this->heal(10);
    }
}