#include "mercenary.hpp"
#include "../../../../Ej3/team.hpp"

Mercenary::Mercenary(string name, shared_ptr<Team> currentTeam): 
    Warrior(name, MERCENARY, 0), allysRemaining(1), currentTeam(currentTeam) 
{}

int Mercenary::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE + Warrior::useWeapon(weapon, target, targetTeam);

    cout << name << " (Mercenary) attacks " << target->getName() << " (" << target->getType() << ")";

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
            //add mercenary to vsTeam.
            objective->members.push_back(shared_from_this());
            cout << name << " has betrayed their team!" << endl;
            this->currentTeam = objective;
            return;
        }
    }
    cout << "Mercenary is not in this team." << endl;
}

void Mercenary::stealWeapon(shared_ptr<Character> target){
    cout << name << " attempts to steal a weapon from " << target->getName() << "!" << endl;
    cout << "Select a weapon to steal." << endl;

    if (target->inventory().first && target->inventory().second){
        cout << "1. " << target->inventory().first->getName() << endl;
        cout << "2. " << target->inventory().second->getName() << endl;
    } else if (target->inventory().first){
        cout << "1. " << target->inventory().first->getName() << endl;
    } else if (target->inventory().second){
        cout << "1. " << target->inventory().second->getName() << endl;
    } else {
        cout << target->getName() << " has no weapons to steal!" << endl;
        return;
    }

    int choice=1;
    //cin >> choice;

    shared_ptr<Weapon> stolenWeapon = nullptr;
    switch (choice){
        case 1:
            if (target->inventory().first) stolenWeapon = target->inventory().first;
            else {
                stolenWeapon = target->inventory().second;
                return;
            }
            break;
        case 2: stolenWeapon = target->inventory().second; break;
        default:
            cout << "Invalid choice." << endl;
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
    currentTeam->showMembers();
}