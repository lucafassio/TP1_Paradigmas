#include "warrior.hpp"

Warrior::Warrior(string name, CharacterType type):
    name(name), type(type), health(100), armor(0), combatBuff(0), weapons(nullptr, nullptr)
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

void Warrior::heal(int amount) {
    health += amount;
    if (health > 100) health = 100; //no se puede curar mas del maximo de vida.
}

void Warrior::reciveDamage(int dam){
    if (immune){
        immune = false;
        cout << name << " is immune right now!" << endl;
        return;
    }
    health-=dam;
    if (health<0){
        health=0;
        //muere
    }
}

int Warrior::getBuff() const {
    return combatBuff;
}

string Warrior::getType() const {
    switch (type){
        case BARBARIAN: return "Barbarian"; break;
        case GLADIATOR: return "Gladiator"; break;
        case KNIGHT: return "Knight"; break;
        case MERCENARY: return "Mercenary"; break;
        case PALADIN: return "Paladin"; break;
        case CONJURER: return "Conjurer"; break;
        case NECRO: return "Necromancer"; break;
        case SORCERER: return "Sorcerer"; break;
        case WARLOCK: return "Warlock"; break;
        default: return "Unknown"; break;
    }
}

void Warrior::addWeapon(Weapon* w){
    cout << "Adding weapon. Current weapons: " << weapons.first << ", " << weapons.second << endl;
    if (weapons.first == nullptr) weapons.first = w;
    else if (weapons.second == nullptr) weapons.second = w;
}

pair<Weapon*, Weapon*> Warrior::inventory() const {
    return weapons;
}

int Warrior::useWeapon(Weapon* weapon, Character* target){
    if (!weapon) return 0;

    int weaponDamage = 0;

    //si el arma es de combate, extraigo el daño y agrego el buff de Warrior.
    if (weapon->isCombat()) weaponDamage = weapon->attack() + this->combatBuff;

    //SIN IMPLEMENTAR
    //si el arma es magica se aplicaran los efectos correspondientes.
    if (!weapon->isCombat()){
        //aplicar efectos de magia.
        target->getName(); //para que no me tire warning de variable no usada.
    }

    return weaponDamage;
}

// ======= METODOS PARA MANEJAR EFECTOS ======= //
void Warrior::applyEffect(Effect effect, int duration){
    currentEffects.push_back(make_pair(effect, duration));
}

void Warrior::effectUpdate(){
    for (auto effect = this->currentEffects.begin(); effect != this->currentEffects.end();){
        if (effect->second == 0){
            effect = this->currentEffects.erase(effect);
        }
        else{
            switch (effect->first){
                case REGENERATION: this->regenCase(); break;
                case STRENGTH: this->strengthCase(); break;
                case BURNING: this->burnCase(); break;
                case POISON: this->poisonCase(); break;
                case LUCK: this->luckCase(); break;
                case STUN: this->stunCase(); break;
                case IMMUNITY: this->immunityCase(); break;
                case INVISIBILITY: this->invisibilityCase(); break;
            }
        }
        effect->second--;
        effect++;
    }
}

void Warrior::regenCase(){
    this->health += 5;
    if (this->health > 100) this->health = 100; //no se puede curar mas del maximo de vida.
}

void Warrior::strengthCase(){
    this->strengthBuff = true; //activa el buff de fuerza.
}

void Warrior::burnCase(){
    health -= 5;
    if (health < 0) health = 0; //no se puede morir por veneno.
}

void Warrior::poisonCase(){
    health -= 5;
    if (health < 1) health = 1; //el veneno nunca es letal.
}

void Warrior::stunCase(){
    stunned = true; //el proximo turno no puede atacar.
}

void Warrior::luckCase(){
    int randomValue = rand() % 100;
    if (randomValue < 20){ //20% de chances de conseguir doble buff.
        opponentMiss = true;
        forcedCritical = true;
    }
    else if (randomValue < 80){ //60% de solo generar miss o critical (50/50).
        int buffType = rand() % 2;
        if (buffType == 0) opponentMiss = true; //proximo golpe recibido sera un miss.
        else forcedCritical = true; //proximo ataque sera un critico (x1.5 de daño).
    }
    // 20% de chances de que no pase nada, se gasta igualmente el efecto.
}

void Warrior::immunityCase(){
    immune = true;
}

void Warrior::invisibilityCase(){
    opponentMiss = true;
}
