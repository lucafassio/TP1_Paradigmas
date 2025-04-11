#include "gladiator.hpp"

Gladiator::Gladiator(string name): 
    Warrior(name, GLADIATOR, 8){
    combatBuff = 3;
}

int Gladiator::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE + Warrior::useWeapon(weapon, target, targetTeam);

    cout << name << " (Gladiator) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon) cout << " with " << weapon->getName();
    else cout << " with bare hands";

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

    if (lastStandActive){
        finalDamage *= 2; //aumento daño por Last Stand.
    }

    //aplicar daño al oponente.
    target->receiveDamage(finalDamage);
    if (!target->getHealth()) targetTeam->loseMember(target);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

void Gladiator::receiveDamage(int damage){
    if (lastStandActive) return;
    Warrior::receiveDamage(damage);
}

void Gladiator::activateLastStand() {
    if (lastStandCooldown == 0) {
        lastStandActive = true;
        lastStandCooldown = 4;
    }
}

bool Gladiator::isLastStandActive() const {
    return lastStandActive;
}

void Gladiator::endTurnUpdate(shared_ptr<Team> currentTeam) {
    Warrior::effectUpdate(currentTeam);
    if (lastStandActive) lastStandActive = false;
    if (lastStandCooldown > 0) lastStandCooldown--;
    if (!this->health) currentTeam->loseMember(shared_from_this());
}
