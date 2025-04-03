#include "warrior.hpp"

#ifndef INCLUDED_CORRECTLY
#error "Header not included correctamente!"
#endif

Warrior::Warrior(string name): 
    name(name), health(100), armor(0), combatBuff(0), weapons(nullptr, nullptr)
{}

string Warrior::getName() const {
    return name;
}

int Warrior::getHealth() const {
    return health;
}

int Warrior::getArmor() const {
    return armor;
}

void Warrior::reciveDamage(int dam){
    health-=dam;
    if (health<0){
        health=0;
        //muere
    }
}

int Warrior::getBuff() const {
    return combatBuff;
}

void Warrior::addWeapon(Weapon* w){
    cout << "Adding weapon. Current weapons: " << weapons.first << ", " << weapons.second << endl;
    if (weapons.first == nullptr) weapons.first = w;
    else if (weapons.second == nullptr) weapons.second = w;
}

std::pair<Weapon*, Weapon*> Warrior::inventory() const {
    return weapons;
}

int Warrior::useWeapon(Weapon* w, Character* op){
    if (!w) return BASE_DAMAGE;
    if (w->isCombat()){
        int fullDamage=BASE_DAMAGE + w->attack();
        op->reciveDamage(fullDamage);
        return fullDamage;
    }
    return 0;
}

