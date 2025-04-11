#include "conjurer.hpp"

Conjurer::Conjurer(string name):
    Mage(name, CONJURER, 100), shielded(false), cooldown(0), empoweredDamage(0)
{}

int Conjurer::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE + Mage::useWeapon(weapon, target, targetTeam);

    cout << name << " (Conjurer) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon) cout << " with " << weapon->getName();
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
    target->receiveDamage(finalDamage);
    if (!target->getHealth()) targetTeam->loseMember(target);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

void Conjurer::summonShield() {
    this->shielded = true;
    this->cooldown = 1;
}

bool Conjurer::isShielded() const {
    return shielded;
}

void Conjurer::updateCooldown() {
    if (cooldown > 0) cooldown--;
    if (cooldown == 0) shielded = false;
}

void Conjurer::applyEffectTo(shared_ptr<Character> target, Effect effectType) {
    target->applyEffect(effectType, 2);
}

bool Conjurer::canUseShield() const {
    return cooldown == 0;
}

void Conjurer::empowerAttribute() {
    if (health <= 10) return;
    this->health -= 10;
    this->empoweredDamage += 5;
}
