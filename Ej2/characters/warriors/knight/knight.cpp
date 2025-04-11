#include "knight.hpp"

Knight::Knight(string name): 
    Warrior(name, KNIGHT, 25), turnsWithIronWill(0), cooldownIronWill(0), ironWillActive(false) 
{}

int Knight::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE + Warrior::useWeapon(weapon, target, targetTeam);

    cout << name << " (Knight) attacks " << target->getName() << " (" << target->getType() << ")";

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

void Knight::ironWill(){
    if (cooldownIronWill == 0){
        this->armor += 15;
        this->combatBuff += 5;
        this->ironWillActive = true;
        this->cooldownIronWill = 4;
    }
}

void Knight::endTurnUpdate(shared_ptr<Team> currentTeam){
    Warrior::effectUpdate(currentTeam);
    if (cooldownIronWill > 0) cooldownIronWill--;

    if (ironWillActive){
        turnsWithIronWill++;
        if (turnsWithIronWill >= 2) {
            this->armor -= 15;
            this->combatBuff -= 5;
            this->ironWillActive = false;
            this->turnsWithIronWill = 0;
        }
    }
    if (!this->health) currentTeam->loseMember(shared_from_this());
}
