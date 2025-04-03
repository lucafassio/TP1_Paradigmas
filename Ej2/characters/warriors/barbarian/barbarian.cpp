#include "barbarian.hpp"

Barbarian::Barbarian(string name): 
    Warrior(name)
{srand(time(nullptr));}

int Barbarian::useWeapon(Weapon* w, Character* op){
    //verificar si se activa rage (20% de probabilidad).
    if (!isInRage() && (rand() % 100) < 20){
        rageAttacksLeft=2;
        cout << name << " enters RAGE mode!" << endl;
    }

    cout << name << " attacks " << op->getName();

    int fullDamage = BASE_DAMAGE;
    if(w){
        if (w->isCombat()) fullDamage += w->attack();
        cout << " with " << w->getName();
    }
    else cout << " with bare hands";

    //aplicar multiplicador de daño si está en rage.
    if (isInRage()){
        fullDamage = static_cast<int>(fullDamage * RAGE_DAMAGE_MULTIPLIER);
        decreaseRageTurns();
    }

    //aplicar daño al oponente.
    op->reciveDamage(fullDamage);
    cout << " and deals " << fullDamage << " damage!" << endl;
    return fullDamage;
}

bool Barbarian::isInRage() const {
    return rageAttacksLeft > 0;
}

void Barbarian::decreaseRageTurns(){
    if(rageAttacksLeft > 0) rageAttacksLeft--;
}