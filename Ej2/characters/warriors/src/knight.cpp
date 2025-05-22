#include "../headers/knight.hpp"

Knight::Knight(string name): 
    Warrior(name, KNIGHT, 100, 25), timesWithIronWill(0), cooldownIronWill(0)
{}

string Knight::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) {
    string logText;
    int finalDamage = BASE_DAMAGE;

    logText += name + " (Knight) attacks " + target->getName() + " (" + target->getType() + ")";

    if (weapon) {
        if (weapon->isCombat()) finalDamage += weapon->attack() + this->combatBuff;
        logText += " with " + weapon->getName();
    } else {
        logText += " with bare hands";
    }

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde.
    if (hasEffect(SCARED) && rand() % 100 < 60) {
        logText += ". " + name + " (Knight) is scared and misses the attack!\n";
        return logText;
    }

    if (stunned) {
        logText += ". " + name + " (Knight) is stunned!\n";
        stunned = false;
        return logText;
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (forcedCritical) {
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //reparto el daño para cuando el warlock haga Soul Link.
    logText += Warrior::warlockSoulLink(target, targetTeam, finalDamage);

    if ((target->getType() == "Barbarian" || target->getType() == "Gladiator") && rand() % 100 < 20 && target->getHealth()) {
        //los barbaros y gladiadores tienen un 20% de chance de contraatacar haciendo un 40% menos de daño.
        this->receiveDamage(finalDamage * 0.6);
        logText += target->getName() + " (" + target->getType() + ") counterattacks!\n";
    }

    return logText;
}

string Knight::ironWill(){
    this->armor += 15;
    this->combatBuff += 5;
    this->cooldownIronWill = 1;
    timesWithIronWill++;
    cout << name << " (Knight) uses Iron Will!" << endl;
    return name + " (Knight) uses Iron Will!\n";
}

int Knight::getIronWillCooldown() const {
    return cooldownIronWill;
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
