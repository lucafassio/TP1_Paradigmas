#include "mage.hpp"
#include "../../../Ej3/team.hpp"

Mage::Mage(string name, CharacterType type, int health, int mana):
    name(name), type(type), health(health), mana(mana), weapons(nullptr, nullptr)
{}

string Mage::getName() const {
    return name;
}

int Mage::getHealth() const {
    return health;
}

int Mage::getMana() const {
    return mana;
}

int Mage::getBuff() const {
    return magicBuff;
}

void Mage::heal(int amount) {
    health += amount;
    if (health > 100) health = 100; //no se puede curar mas del maximo de vida.
}

void Mage::reciveDamage(int dam){
    if (opponentMiss) {
        cout << name << " dodges the attack!" << endl;
        opponentMiss = false;
        return;
    }
    health-=dam;
    if (health<0){
        health=0;
    }
}

string Mage::getType() const {
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

void Mage::addWeapon(shared_ptr<Weapon> w){
    if (weapons.first == nullptr) weapons.first = w;
    else if (weapons.second == nullptr) weapons.second = w;
}

pair<shared_ptr<Weapon>, shared_ptr<Weapon>> Mage::inventory() const {
    return weapons;
}

int Mage::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    if (!targetTeam) return 0;
    if (!weapon) return 0;

    int weaponDamage = 0;

    if (weapon->isCombat()) weaponDamage = weapon->attack();

    //SIN IMPLEMENTAR
    //si el arma es magica se aplicaran los efectos correspondientes.
    if (!weapon->isCombat()){
        //aplicar efectos de magia.
        target->getName(); //para que no me tire warning de variable no usada.
    }

    return weaponDamage;
}

void Mage::loseWeapon(shared_ptr<Weapon> weapon){
    if (weapons.first == weapon) weapons.first = nullptr;
    else if (weapons.second == weapon) weapons.second = nullptr;
    else cout << "Weapon not found in inventory." << endl;
}

// ======= METODOS PARA MANEJAR EFECTOS ======= //
void Mage::applyEffect(Effect effect, int duration) {
    currentEffects.push_back(make_pair(effect, duration));
}

void Mage::effectUpdate(shared_ptr<Team> currentTeam){
    for (auto effect = this->currentEffects.begin(); effect != this->currentEffects.end();){
        if (effect->second == 0){
            effect = this->currentEffects.erase(effect);
        } 
        else{
            switch (effect->first){
                case REGENERATION: this->regenCase(); break;
                case STRENGTH: this->strengthCase(); break;
                case BURNING: this->burnCase(); break;
                case BLEEDING: this->bleedCase(); break;
                case POISON: this->poisonCase(); break;
                case LUCK: this->luckCase(); break;
                case STUN: this->stunCase(); break;
                case IMMUNITY: this->immunityCase(); break;
                case INVISIBILITY: this->invisibilityCase(); break;
            }
            if (!this->health) currentTeam->loseMember(shared_from_this());
        }
        effect->second--; 
    }
}

void Mage::regenCase(){
    this->health += 5;
    if (this->health > 100) this->health = 100; //no se puede curar mas del maximo de vida.
}

void Mage::strengthCase(){
    this->strengthBuff = true; //activa el buff de fuerza.
}

void Mage::burnCase(){
    if (!immune) health -= 5;
    if (health < 0) health = 0;
}

void Mage::bleedCase(){
    health -= 5;
    if (health < 0) health = 0;
}

void Mage::poisonCase(){
    if (!immune) health -= 5;
    if (health < 1) health = 1; //el veneno nunca es letal.
}

void Mage::stunCase(){
    stunned = true; //el proximo turno no puede atacar.
}

void Mage::luckCase(){
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

void Mage::immunityCase(){
    immune = true;
}

void Mage::invisibilityCase(){
    opponentMiss = true;
}
