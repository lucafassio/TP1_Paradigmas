#include "Larry.hpp"
#include "../../../../Ej3/team.hpp"
#include "../warlock/warlock.hpp"

Larry::Larry():
    //pongo tipo necro pero no afecta en nada porque overrideo el metodo getType.
    Mage("Larry", NECRO, 30, 0)
{}

string Larry::getType() const {
    return "Skelly";
}

//el skelly no tiene mana, no puede usar armas y no puede curarse.
int Larry::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = SKELETON_DAMAGE;

    cout << name << " (Skelly) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon){
        if (weapon->isCombat()) finalDamage += weapon->attack();
        cout << " with " << weapon->getName();
    } 
    else cout << " with his little sword";

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (hasEffect(SCARED) && rand() % 100 < 60){
        cout << ". " << name << " (Skelly) is scared and misses the attack!" << endl;
        return 0; //no hace daño.
    }

    if (stunned){
        cout << ". " << name << " (Skelly) is stunned!" << endl;
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

void Larry::loseLifetime(){
    lifetimeRemaining--;
    if (lifetimeRemaining == 0) cout << "Larry has died!" << endl;
}