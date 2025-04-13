#include "conjurer.hpp"
#include "../warlock/warlock.hpp"

Conjurer::Conjurer(string name):
    Mage(name, CONJURER, 100, 100), shielded(false), cooldown(0), empoweredDamage(0)
{}

int Conjurer::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE;

    cout << name << " (Conjurer) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon){
        if (weapon->isCombat()) finalDamage += weapon->attack();
        cout << " with " << weapon->getName();
    } 
    else cout << " with his own power";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        cout << ". " << name << " (Conjurer) is scared and misses the attack!" << endl;
        return 0; //no hace daño.
    }

    if (stunned){
        cout << ". " << name << " (Conjurer) is stunned!" << endl;
        return 0; //no hace daño.
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (forcedCritical){
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //reparto el daño para cuando el warlock haga Soul Link.
    Mage::warlockSoulLink(target, targetTeam, finalDamage);

    if ((target->getType() == "Barbarian" || target->getType() == "Gladiator") && rand() % 100 < 20 && target->getHealth()){
        //los barbaros y gladiadores tienen un 20% de chance de contraatacar haciendo un 40% menos de daño.
        this->receiveDamage(finalDamage * 0.6);
        cout << target->getName() << " (" << target->getType() << ") counterattacks!" << endl;
    }

    return finalDamage;
}

void Conjurer::summonShield() {
    this->shielded = true;
    this->cooldown = 1;
}

bool Conjurer::isShielded() const {
    return shielded;
}

void Conjurer::updateCooldown(){
    if (cooldown > 0) cooldown--;
    if (cooldown == 0) shielded = false;
}

void Conjurer::applyEffectTo(shared_ptr<Character> target, Effect effectType) {
    target->applyEffect(effectType, 2);
}

bool Conjurer::canUseShield() const {
    return cooldown == 0;
}

void Conjurer::empowerAttribute(){
    if (health <= 10) return;
    this->health -= 10;
    this->empoweredDamage += 5;
}
