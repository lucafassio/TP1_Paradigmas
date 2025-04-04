#include "mage.hpp"
#include "../../weapons/weapon.hpp"

Mage::Mage(string name)
    : name(name), health(100), mana(100), magicPower(50), spellSlots(3){
}

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
    return magicPower;
}

void Mage::reciveDamage(int dam) {
    health -= dam;
}

void Mage::addWeapon(Weapon* w) {
    if (weapons.first == nullptr) {
        weapons.first = w;
    } else if (weapons.second == nullptr) {
        weapons.second = w;
    }
    // If both slots are full, the weapon is not added
}

pair<Weapon*, Weapon*> Mage::inventory() const {
    return weapons;
}

int Mage::useWeapon(Weapon* w, Character* op) {
    if (!w) return 0; // No weapon to use
    if (w->isCombat()) {
        int fullDamage = magicPower + w->attack();
        op->reciveDamage(fullDamage);
        return fullDamage;
    }
    return 0; // Non-combat weapon, no damage dealt
}

int Mage::getMagicPower() const {
    return magicPower;
}

int Mage::getSpellSlots() const {
    return spellSlots;
}

void Mage::castSpell(const string& spellName) {
    if (spellSlots > 0) {
        cout << name << " casts " << spellName << "!" << endl;
        spellSlots--;
    } else {
        cout << name << " has no spell slots left!" << endl;
    }
}

string Mage::getType() const {
    switch (type) {
        case CONJURER: return "Conjurer"; break;
        case NECRO: return "Necromancer"; break;
        case SORCERER: return "Sorcerer"; break;
        case WARLOCK: return "Warlock"; break;
        default: return "Unknown"; break;
    }
}

void Mage::heal(int amount) {
    health += amount;
    if (health > 100) health = 100; // Max health cap
}

// ======= METODOS PARA MANEJAR EFECTOS ======= //
void Mage::applyEffect(Effect effect, int duration) {
    // Implement effect application logic here
    cout << name << " applies effect: " << effect << " for " << duration << " turns." << endl;
}

void Mage::effectUpdate(){
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
    health -= 5;
    if (health < 0) health = 0; //no se puede morir por veneno.
}

void Mage::poisonCase(){
    health -= 5;
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
