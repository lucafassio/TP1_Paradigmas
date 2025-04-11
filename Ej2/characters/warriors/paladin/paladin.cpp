#include "paladin.hpp"

Paladin::Paladin(string name): 
    Warrior(name, PALADIN, 30), divineShieldCooldown(0), hasDivineShield(false)
{}

int Paladin::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE + Warrior::useWeapon(weapon, target, targetTeam);

    cout << name << " (Paladin) attacks " << target->getName() << " (" << target->getType() << ")";

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

    //aplicar daño al oponente.
    target->receiveDamage(finalDamage);
    if (!target->getHealth()) targetTeam->loseMember(target);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

void Paladin::receiveDamage(int damage){
    if (hasDivineShield){
        cout << name << " is protected by Divine Shield!" << endl;
        hasDivineShield = false;
        return;
    }
    Warrior::receiveDamage(damage);
}

void Paladin::healingTeam(shared_ptr<Character> target1, shared_ptr<Character> target2){
    if (target1) target1->heal(20);
    if (target2) target2->heal(20);
}

void Paladin::divineShield(){
    if (divineShieldCooldown == 0) {
        hasDivineShield = true;
        divineShieldCooldown = 3;
    }
}

void Paladin::endTurnUpdate(shared_ptr<Team> currentTeam){
    Warrior::effectUpdate(currentTeam);
    if (divineShieldCooldown > 0) divineShieldCooldown--;
    if (divineShieldCooldown == 0) hasDivineShield = false;
    if (!this->health) currentTeam->loseMember(shared_from_this());
}