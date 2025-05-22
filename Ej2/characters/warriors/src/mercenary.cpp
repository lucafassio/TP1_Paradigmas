#include "../headers/mercenary.hpp"

Mercenary::Mercenary(string name, shared_ptr<Team> currentTeam): 
    Warrior(name, MERCENARY, 100, 0), allysRemaining(1), currentTeam(currentTeam) 
{}

string Mercenary::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) {
    string logText;
    int finalDamage = BASE_DAMAGE;

    logText += name + " (Mercenary) attacks " + target->getName() + " (" + target->getType() + ")";

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
        logText += ". " + name + " (Mercenary) is scared and misses the attack!\n";
        return logText;
    }

    if (stunned) {
        logText += ". " + name + " (Mercenary) is stunned!\n";
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

void Mercenary::entersTeam(shared_ptr<Team> team){
    currentTeam = team;
    cout << name << " has joined the team!" << endl;
}

void Mercenary::receiveDamage(int damage){
    Warrior::receiveDamage(damage);
    if (health <= 30)
        if ((rand() % 100) < 20) runAway();
}

void Mercenary::runAway(){
    cout << name << " has run away!" << endl;
    currentTeam->loseMember(shared_from_this());
}

void Mercenary::betray(shared_ptr<Team> currentTeam, shared_ptr<Team> objective){
    //delete mercenary from current team.
    for (auto it = currentTeam->members.begin(); it != currentTeam->members.end(); ++it) {
        if (*it == shared_from_this()){
            currentTeam->members.erase(it);
            //add mercenary to objective.
            objective->members.push_back(shared_from_this());
            cout << name << " betrayed his team!" << endl;
            this->currentTeam = objective;
            return;
        }
    }
    cout << "Mercenary is not in this team." << endl;
}

string Mercenary::getInvisible(){
    this->applyEffect(INVISIBILITY, 3);
    if (rand() % 100 < 30) runAway();
    return name + " has become invisible!\n";
}

string Mercenary::recruitAlly(){
    currentTeam->members.push_back(make_shared<Mercenary>(this->getName() + "'s Ally", currentTeam));
    return name + "'s Ally has been recruited!\n";
}

int Mercenary::getAllysRemaining() const {
    return allysRemaining;
}