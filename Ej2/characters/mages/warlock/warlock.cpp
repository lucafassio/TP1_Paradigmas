#include "warlock.hpp"
#include "../../../../Ej3/team.hpp"

using namespace std;

Warlock::Warlock(string name): 
    Mage(name, WARLOCK, 100, 100), soulLinkCooldown(0), ultimateCooldown(0)
{}

string Warlock::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) {
    string logText;
    int finalDamage = BASE_DAMAGE;

    logText += name + " (Warlock) attacks " + target->getName() + " (" + target->getType() + ")";

    if (weapon) {
        if (weapon->isCombat()) finalDamage += weapon->attack();
        logText += " with " + weapon->getName();
    } else {
        logText += " with his own power";
    }

    //aplico el buff de STRENGTH si corresponde.
    if (hasEffect(STRENGTH)) finalDamage = static_cast<int>(finalDamage * 1.5);

    //aplico el debuff de SCARED si corresponde.
    if (hasEffect(SCARED) && rand() % 100 < 60) {
        logText += ". " + name + " (Warlock) is scared and misses the attack!\n";
        cout << logText; // Print the log at the end
        return logText;
    }

    if (stunned) {
        logText += ". " + name + " (Warlock) is stunned!\n";
        cout << logText; // Print the log at the end
        return logText;
    }

    //siempre existe un 20% de probabilidad de activar un crítico (si ya venia forzado se mantiene igual).
    if ((rand() % 100) < 20) forcedCritical = true;

    if (forcedCritical) {
        finalDamage = static_cast<int>(finalDamage * 1.5); //aumento daño por critico.
        forcedCritical = false;
    }

    //probabilidad de aplicar efectos adicionales.
    int roll = rand() % 100;
    if (roll < 15) {
        target->receiveDamage(10);
        this->heal(10);
        logText += ". Warlock drains 10 health from " + target->getName();
    } else if (roll < 25) {
        target->applyEffect(BLEEDING, 2);
        logText += ". Warlock applies BLEEDING to " + target->getName();
    } else if (roll < 45) {
        target->applyEffect(MANA_LEECH, 2);
        this->mana += 15;
        logText += ". Warlock leeches mana from " + target->getName();
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

void Warlock::soulLink(shared_ptr<Team> ownTeam){
    if (soulLinkCooldown > 0) return;

    for (const auto& member : ownTeam->getMembers())
        if (member->getHealth() > 0){
            linkedAllies.push_back(member);
            member->applyEffect(SOUL_LINKED, 3);
        }
    soulLinkCooldown = 0;
}

void Warlock::bornAgain(shared_ptr<Team> ownTeam){
    vector<shared_ptr<Character>> deadAllies;
    for (const auto& member : ownTeam->getMembers()){
        if (!member->getHealth()) deadAllies.push_back(member);
    }
    for (const auto& member : deadAllies)
        member->heal(member->getMaxHealth() / static_cast<int>(deadAllies.size()));
}

void Warlock::updateCooldowns(){
    if (soulLinkCooldown > 0) soulLinkCooldown--;
    if (ultimateCooldown > 0) ultimateCooldown--;
    if (soulLinkCooldown == 0) breakSoulLink();
}

void Warlock::breakSoulLink(){
    linkedAllies.clear();
}
