#include "barbarian.hpp"

Barbarian::Barbarian(string name): 
    Warrior(name, BARBARIAN)
{srand(time(nullptr));}

int Barbarian::useWeapon(Weapon* weapon, Character* target){
    int finalDamage = BASE_DAMAGE + Warrior::useWeapon(weapon, target);

    //verificar si se activa rage (20% de probabilidad).
    if (!isInRage() && (rand() % 100) < 20){
        rageAttacksLeft=2;
        cout << name << " (Barbarian) enters RAGE mode!" << endl;
    }

    cout << name << " (Barbarian) attacks " << target->getName() << " (" << target->getType() << ")";

    if(weapon) cout << " with " << weapon->getName();
    else cout << " with bare hands";

    //aplicar multiplicador de daño si está en rage.
    if (isInRage()){
        finalDamage = static_cast<int>(finalDamage * RAGE_DAMAGE_MULTIPLIER);
        decreaseRageTurns();
    }

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
    target->reciveDamage(finalDamage);
    cout << " and deals " << finalDamage << " damage!" << endl;

    return finalDamage;
}

bool Barbarian::isInRage() const {
    return rageAttacksLeft > 0;
}

void Barbarian::decreaseRageTurns(){
    if(rageAttacksLeft > 0) rageAttacksLeft--;
}