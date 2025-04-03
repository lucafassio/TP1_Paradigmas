#include "barbarian.hpp"

Barbarian::Barbarian(string name): 
    Warrior(name)
{srand(time(nullptr));}

int Barbarian::useWeapon(Weapon* w, Character* op){
    //verificar si se activa rage (20% de probabilidad).
    if (!isInRage() && (rand()%100)<20){
        rageAttacksLeft=2;
        cout << name << " enters RAGE mode!" << endl;
    }

    //calcular daño base usando la implementación del guerrero.
    int baseDamage=Warrior::useWeapon(w, op);

    cout << name << " attacks with " << baseDamage << " damage." << endl;

    //aplicar multiplicador de daño si está en rage.
    if (isInRage()){
        baseDamage=static_cast<int>(baseDamage*RAGE_DAMAGE_MULTIPLIER);
        decreaseRageTurns();
    }
    return baseDamage;
}

bool Barbarian::isInRage() const {
    return rageAttacksLeft>0;
}

void Barbarian::decreaseRageTurns(){
    if(rageAttacksLeft>0) rageAttacksLeft--;
}