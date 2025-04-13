#include "knight.hpp"
#include "../../mages/warlock/warlock.hpp"

Knight::Knight(string name): 
    Warrior(name, KNIGHT, 100, 25), timesWithIronWill(0), cooldownIronWill(0)
{}

int Knight::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE;

    cout << name << " (Knight) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon){
        if (weapon->isCombat()) finalDamage += weapon->attack() + this->combatBuff;
        cout << " with " << weapon->getName();
    } 
    else cout << " with bare hands";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        cout << ". " << name << " (Knight) is scared and misses the attack!" << endl;
        return 0; //no hace daño.
    }

    if (stunned){
        cout << ". " << name << " (Knight) is stunned!" << endl;
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

void Knight::ironWill(){
    if (cooldownIronWill == 0){
        this->armor += 15;
        this->combatBuff += 5;
        this->cooldownIronWill = 3;
        timesWithIronWill++;
    }
}

void Knight::receiveDamage(int damage){
    Warrior::receiveDamage(damage);
    if (!this->health){
        this->armor -= 15 * timesWithIronWill;
        this->combatBuff -= 5 * timesWithIronWill;
        this->cooldownIronWill = 0;
        this->timesWithIronWill = 0;
    }
}

void Knight::endTurnUpdate(){
    Warrior::effectUpdate();
    if (cooldownIronWill > 0) cooldownIronWill--;
}
