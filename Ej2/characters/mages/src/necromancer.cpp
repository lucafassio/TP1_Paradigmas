#include "../headers/necromancer.hpp"

Necromancer::Necromancer(string name): 
    Mage(name, NECRO, 100, 100)
{}

string Necromancer::useWeapon(unique_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    string logText;
    int finalDamage = BASE_DAMAGE;

    logText += this->name + " (Necromancer) attacks " + target->getName() + " (" + target->getType() + ")";

    if (weapon && weapon->isCombat()){
        finalDamage += weapon->attack();
        logText += " with " + weapon->getName();
    } 
    else logText += " with his own power";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        logText += ". " + name + " (Necromancer) is scared and misses the attack!\n";
        return logText;
    }

    if (this->stunned){
        logText += ". " + name + " (Necromancer) is stunned!\n";
        this->stunned = false;
        return logText;
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) this->forcedCritical = true;

    if (this->forcedCritical){
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //reparto el daño para cuando el warlock haga Soul Link.
    logText += Mage::warlockSoulLink(target, targetTeam, finalDamage);

    if ((target->getType() == "Barbarian" || target->getType() == "Gladiator") && rand() % 100 < 20 && target->getHealth()) {
        //los barbaros y gladiadores tienen un 20% de chance de contraatacar haciendo un 40% menos de daño.
        this->receiveDamage(finalDamage * 0.6);
        logText += target->getName() + " (" + target->getType() + ") counterattacks!\n";
    }

    cout << logText; // Print the log at the end
    return logText;
}

string Necromancer::raiseDead(shared_ptr<Team> currentTeam){
    string logText;
    if (this->mana >= 25 && this->larrysCounter < 3){
        logText += this->name + " raises Larry from the dead!\n";
        currentTeam->members.push_back(static_pointer_cast<Character>(make_shared<Larry>()));
        currentTeam->members.back()->heal(1); //se inicializa con 100 de vida y asi se la bajo al maximo que tiene.
        larrysCounter++;
        mana -= 25;
    }
    else if (larrysCounter >= 3) logText += name + " has already raised Larry 3 times!\n";
    else logText += name + " doesn't have enough mana to raise Larry!\n";
    return logText;
}

string Necromancer::drainLife(shared_ptr<Character> target){
    string logText;
    if (mana >= 10){
        logText += name + " drains 10 life from " + target->getName();
        target->receiveDamage(10);
        if (!target->getHealth()) logText += " taking him to the death world";
        logText += "!\n";
        this->heal(10);
    }
    return logText;
}

string Necromancer::reviveTeammate(shared_ptr<Character> target){
    string logText;
    if (mana >= 20 && !target->getHealth()){
        logText += name + " (Necromancer) revives " + target->getName() + " (" + target->getType() + ")\n";
        target->heal(30);
        mana -= 20;
    }
    else if (target->getHealth()) logText += target->getName() + " is not dead!\n";
    else logText += name + " doesn't have enough mana to revive " + target->getName() + "!\n";
    return logText;
}