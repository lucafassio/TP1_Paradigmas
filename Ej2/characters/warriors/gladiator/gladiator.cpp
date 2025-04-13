#include "gladiator.hpp"
#include "../../mages/warlock/warlock.hpp"

Gladiator::Gladiator(string name): 
    Warrior(name, GLADIATOR, 100, 8){
    combatBuff = 3;
}

int Gladiator::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE;

    cout << name << " (Gladiator) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon){
        if (weapon->isCombat()) finalDamage += weapon->attack() + this->combatBuff;
        cout << " with " << weapon->getName();
    } 
    else cout << " with bare hands";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        cout << ". " << name << " (Gladiator) is scared and misses the attack!" << endl;
        return 0; //no hace daño.
    }

    if (stunned){
        cout << ". " << name << " (Gladiator) is stunned!" << endl;
        return 0; //no hace daño.
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (forcedCritical){
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    if (lastStandActive){
        finalDamage *= 2; //aumento daño por Last Stand.
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

void Gladiator::receiveDamage(int damage){
    if (lastStandActive) return;
    if (gloryActive && rand() % 100 < 60){
        cout << name << " (Gladiator) is protected by Glory! Damage was reduced by 80%" << endl;
        damage = static_cast<int>(damage * 0.2); //60% chances de que se reduzca el daño en un 80%.
    }
    else if (gloryActive && rand() % 100 < 80){
        cout << name << " (Gladiator) is protected by Glory! " << name << " (Gladiator) didnt feel anything" << endl;
        damage = static_cast<int>(damage * 0); //30% chances de que no le peguen.
    }
    Warrior::receiveDamage(damage);
}

void Gladiator::blastOfGlory(shared_ptr<Team> ownTeam, shared_ptr<Team> enemyTeam) {
    if (gloryUsed) return;

    int aliveCount = 0;
    for (auto& member : ownTeam->getMembers()) {
        if (member->getHealth() > 0) aliveCount++;
    }

    if (aliveCount != 1) return;

    for (auto& enemy : enemyTeam->getMembers()) {
        if (enemy->getHealth() > 0) {
            enemy->applyEffect(SCARED, 5);
        }
    }

    combatBuff += 10;
    gloryActive = true;
    gloryUsed = true;
}
