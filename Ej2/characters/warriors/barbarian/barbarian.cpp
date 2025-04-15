#include "barbarian.hpp"
#include "../../../../Ej3/team.hpp"
#include "../../mages/warlock/warlock.hpp"

Barbarian::Barbarian(string name): 
    Warrior(name, BARBARIAN, 100, 3)
{}

string Barbarian::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) {
    string logText;

    //verifico si se activa rage (20% de probabilidad).
    if (!hasEffect(RAGE) && (rand() % 100) < 20) {
        this->applyEffect(RAGE, 3); //aplico el efecto de rage.
        logText += name + " (Barbarian) enters RAGE mode!\n";
    }

    int finalDamage = BASE_DAMAGE;

    logText += name + " (Barbarian) attacks " + target->getName() + " (" + target->getType() + ")";

    if (weapon) {
        if (weapon->isCombat()) finalDamage += weapon->attack() + this->combatBuff;
        logText += " with " + weapon->getName();
    } else {
        logText += " with bare hands";
    }

    //aplicar multiplicador de daño si está en rage.
    if (this->hasEffect(RAGE)) finalDamage = static_cast<int>(finalDamage * RAGE_DAMAGE_MULTIPLIER);

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde. Al barbaro enfurecido no le afecta.
    if (!hasEffect(RAGE) && hasEffect(SCARED) && rand() % 100 < 60) {
        logText += ". " + name + " (Barbarian) is scared and misses the attack!\n";
        cout << logText; // Print the log at the end
        return 0; //no hace daño.
    }

    if (stunned) {
        logText += ". " + name + " (Barbarian) is stunned!\n";
        cout << logText; // Print the log at the end
        return 0; //no hace daño.
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

    cout << logText;
    return logText;
}