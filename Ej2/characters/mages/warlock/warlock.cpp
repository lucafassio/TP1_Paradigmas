#include "warlock.hpp"
#include "../../../../Ej3/team.hpp"
#include <random>

using namespace std;

Warlock::Warlock(string name): 
    Mage(name, WARLOCK, 100), soulLinkCooldown(0), ultimateCooldown(0)
{}

int Warlock::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    int finalDamage = BASE_DAMAGE + Mage::useWeapon(weapon, target, targetTeam);

    cout << name << " (Warlock) attacks " << target->getName() << " (" << target->getType() << ")";

    if (weapon) cout << " with " << weapon->getName();
    else cout << " with his own power";

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

    //probabilidad de aplicar efectos adicionales.
    int roll = rand() % 100;
    if (roll < 15) {target->receiveDamage(10); this->heal(10);}
    else if (roll < 25) target->applyEffect(BLEEDING, 2);
    else if (roll < 45) {target->applyEffect(MANA_LEECH, 2); this->mana += 15;}

    //aplicar daño al oponente.
    target->receiveDamage(finalDamage);
    if (!target->getHealth()) targetTeam->loseMember(target);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

void Warlock::soulLink(shared_ptr<Team> ownTeam){
    if (soulLinkCooldown > 0) return;

    for (const auto& member : ownTeam->getMembers()) {
        if (member->getHealth() > 0 && member.get() != this) {
            linkedAllies.push_back(member);
            member->applyEffect(SOUL_LINKED, 3);
        }
    }
    this->applyEffect(SOUL_LINKED, 3);
    soulLinkCooldown = 3;
}

void Warlock::bornAgain(shared_ptr<Team> ownTeam){
    if (ultimateCooldown > 0 || mana < 30) return;

    int resurrected = 0;
    for (auto& member : ownTeam->getMembers()) {
        if (member->getHealth() <= 0 && resurrected < 2) {
            member->heal(30);
            resurrected++;
        }
    }
    this->heal(20);
    mana -= 30;
    ultimateCooldown = 3;
}

int Warlock::getSoulLinkCooldown() const {
    return soulLinkCooldown;
}

int Warlock::bornAgainCooldown() const {
    return ultimateCooldown;
}

void Warlock::updateCooldowns(){
    if (soulLinkCooldown > 0) soulLinkCooldown--;
    if (ultimateCooldown > 0) ultimateCooldown--;
}

void Warlock::breakSoulLink(){
    linkedAllies.clear();
}

bool Warlock::isLinkedTo(const shared_ptr<Character>& ally) const {
    for (const auto& member : linkedAllies) {
        if (member == ally) return true;
    }
    return false;
}
