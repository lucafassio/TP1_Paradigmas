#include "paladin.hpp"
#include "../../mages/warlock/warlock.hpp"

Paladin::Paladin(string name): 
    Warrior(name, PALADIN, 100, 30), divineShieldHits(0)
{}

int Paladin::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE;

    cout << name << " (Paladin) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon){
        if (weapon->isCombat()) finalDamage += weapon->attack() + this->combatBuff;
        cout << " with " << weapon->getName();
    }
    else cout << " with bare hands";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        cout << ". " << name << " (Paladin) is scared and misses the attack!" << endl;
        return 0; //no hace daño.
    }

    if (stunned){
        cout << ". " << name << " (Paladin) is stunned!" << endl;
        return 0; //no hace daño.
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (forcedCritical){
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //reparto el daño para cuando el warlock haga Soul Link.
    Warrior::warlockSoulLink(target, targetTeam, finalDamage);

    if ((target->getType() == "Barbarian" || target->getType() == "Gladiator") && rand() % 100 < 20 && target->getHealth()){
        //los barbaros y gladiadores tienen un 20% de chance de contraatacar haciendo un 40% menos de daño.
        this->receiveDamage(finalDamage * 0.6);
        cout << target->getName() << " (" << target->getType() << ") counterattacks!" << endl;
    }

    return finalDamage;
}

void Paladin::receiveDamage(int damage){
    if (divineShieldHits){
        cout << name << " is protected by Divine Shield!" << endl;
        divineShieldHits--;
        return;
    }
    Warrior::receiveDamage(damage);
}

void Paladin::healingTeam(shared_ptr<Character> target1, shared_ptr<Character> target2){
    if (target1) target1->heal(20);
    if (target2) target2->heal(20);
}

void Paladin::divineShield(){
    if (divineShieldHits == 0) divineShieldHits = 5;
}

void Paladin::endTurnUpdate(){
    Warrior::effectUpdate();
}