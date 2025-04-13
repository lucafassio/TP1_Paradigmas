#include "mercenary.hpp"
#include "../../../../Ej3/team.hpp"
#include "../../mages/warlock/warlock.hpp"

Mercenary::Mercenary(string name, shared_ptr<Team> currentTeam): 
    Warrior(name, MERCENARY, 100, 0), allysRemaining(1), currentTeam(currentTeam) 
{}

int Mercenary::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE;

    cout << name << " (Mercenary) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon){
        if (weapon->isCombat()) finalDamage += weapon->attack() + this->combatBuff;
        cout << " with " << weapon->getName();
    } 
    else cout << " with bare hands";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        cout << ". " << name << " (Mercenary) is scared and misses the attack!" << endl;
        return 0; //no hace daño.
    }

    if (stunned){
        cout << ". " << name << " (Mercenary) is stunned!" << endl;
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

void Mercenary::entersTeam(shared_ptr<Team> team){
    currentTeam = team;
    cout << name << " has joined the team!" << endl;
}

void Mercenary::receiveDamage(int damage) {
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

void Mercenary::stealWeapon(shared_ptr<Character> target){
    if (this->inventory().first && this->inventory().second){
        cout << "Inventory full." << endl;
        return;
    }
    shared_ptr<Weapon> stolenWeapon = nullptr;

    //si tiene dos armas, elige.
    if (target->inventory().first && target->inventory().second){
        cout << "Select a weapon to steal." << endl;
        cout << "1. " << target->inventory().first->getName() << endl;
        cout << "2. " << target->inventory().second->getName() << endl;

        int choice;
        cin >> choice;
        if (choice == 1) stolenWeapon = target->inventory().first;
        else if (choice == 2) stolenWeapon = target->inventory().second;
        else {
            cout << "Invalid choice." << endl;
            return;
        }

    } 
    //si tiene una sola arma, la roba.
    else if (target->inventory().first){
        stolenWeapon = target->inventory().first;
    } else if (target->inventory().second){
        stolenWeapon = target->inventory().second;
    }
    //si no tiene armas, no puede robar.
    else {
        cout << target->getName() << " has no weapons to steal!" << endl;
        return;
    }

    this->addWeapon(stolenWeapon);
    target->loseWeapon(stolenWeapon);
    cout << name << " has stolen " << stolenWeapon->getName() << " from " << target->getName() << "!" << endl;
}

void Mercenary::getInvisible(){
    this->applyEffect(INVISIBILITY, 1);
}

void Mercenary::recruitAlly(){
    currentTeam->members.push_back(make_shared<Mercenary>(this->getName() + "'s Ally", currentTeam));
}