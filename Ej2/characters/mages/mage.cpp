#include "mage.hpp"
#include "../../../Ej3/team.hpp"
#include "warlock/warlock.hpp"

Mage::Mage(string name, CharacterType type, int maxHealth, int mana):
    name(name), type(type), health(100), maxHealth(maxHealth), mana(mana), weapons(nullptr, nullptr)
{}

string Mage::getName() const {
    return name;
}

int Mage::getHealth() const {
    return health;
}

int Mage::getMaxHealth() const {
    return maxHealth;
}

int Mage::getMana() const {
    return mana;
}

int Mage::getBuff() const {
    return magicBuff;
}

void Mage::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth; //no se puede curar mas del maximo de vida.
}

void Mage::receiveDamage(int dam){
    if (opponentMiss) {
        cout << name << " dodges the attack!" << endl;
        opponentMiss = false;
        return;
    }
    health-=dam;
    if (health <= 0){
        health = 0;
        currentEffects.clear();
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

void Mage::loseWeapon(shared_ptr<Weapon> weapon){
    if (weapons.first == weapon) weapons.first = nullptr;
    else if (weapons.second == weapon) weapons.second = nullptr;
    else cout << "Weapon not found in inventory." << endl;
}

void Mage::endTurnUpdate(){
    this->effectUpdate();
}

string Mage::warlockSoulLink(shared_ptr<Character> target, shared_ptr<Team> targetTeam, int finalDamage){
    string logText;

    shared_ptr<Warlock> opponentWarlock = targetTeam->getWarlock();

    if (target->hasEffect(SOUL_LINKED) && opponentWarlock->linkedAllies.size()) {
        logText += " dealing " + to_string(finalDamage) + " damage to all linked allies!\n";
        int nAlives = static_cast<int>(opponentWarlock->linkedAllies.size());

        for (auto it = opponentWarlock->linkedAllies.begin(); it != opponentWarlock->linkedAllies.end(); it++) {
            auto opponent = *it;

            //el daño total se reparte equitativamente entre los aliados enlazados.
            opponent->receiveDamage(finalDamage / nAlives);
            logText += opponent->getName() + " (" + opponent->getType() + ") receives " + to_string(finalDamage / nAlives) + " damage from Soul Link!\n";

            // si un oponente muere, se corta su vínculo.
            if (!opponent->getHealth()) {
                it = opponentWarlock->linkedAllies.erase(it);
                it--;
            }

            //si no queda nadie enlazado es porque murieron todos.
            if (opponentWarlock->linkedAllies.empty()) break;
        }

        if (!opponentWarlock->getHealth()) opponentWarlock->breakSoulLink();
    } else {
        //aplicar daño al oponente.
        logText += " and deals " + to_string(finalDamage) + " damage!\n";
        target->receiveDamage(finalDamage);
    }

    return logText; // Return the log
}

// ======= METODOS PARA MANEJAR EFECTOS ======= //
void Mage::applyEffect(Effect effect, int duration) {
    currentEffects.push_back(make_pair(effect, duration));
}

bool Mage::hasEffect(Effect effect) const {
    for (const auto& e : currentEffects) {
        if (e.first == effect) return true;
    }
    return false;
}

void Mage::effectUpdate(){
    for (auto effect = this->currentEffects.begin(); effect != this->currentEffects.end();){
        if (effect->second == 0){
            effect = this->currentEffects.erase(effect);
        } 
        else{
            switch (effect->first){
                case REGENERATION: this->regenCase(); break;
                case STRENGTH: break; //no se aplica aca.
                case BURNING: this->burnCase(); break;
                case BLEEDING: this->bleedCase(); break;
                case POISON: this->poisonCase(); break;
                case LUCK: this->luckCase(); break;
                case STUN: this->stunCase(); break;
                case IMMUNITY: break; //no se aplica aca.
                case INVISIBILITY: this->invisibilityCase(); break;
                case FROZEN: this->frozenCase(); break;
                case STONE_SKIN: this->stoneSkinCase(); break;
                case MAGIC_SILENCE: this->magicSilenceCase(); break;
                case ELEMENTAL_EXPOSURE: this->elementalExposureCase(); break;
                case SOUL_LINKED: break; //no se aplica aca.
                case MANA_LEECH: this->manaLeechCase(); break;
                case SCARED: break; //no se aplica aca.
                case RAGE: break; //no se aplica aca.
            }
        }
        effect->second--; 
    }
}

void Mage::regenCase(){
    this->health += 5;
    if (this->health > 100) this->health = 100; //no se puede curar mas del maximo de vida.
}

void Mage::burnCase(){
    if (!hasEffect(IMMUNITY)) health -= 5;
    if (health < 0) health = 0;
}

void Mage::bleedCase(){
    health -= 5;
    if (health < 0) health = 0;
}

void Mage::poisonCase(){
    if (!hasEffect(IMMUNITY)) health -= 5;
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

void Mage::invisibilityCase(){
    opponentMiss = true;
}

void Mage::frozenCase(){
    stunned = true; //el proximo turno no puede atacar.
}

void Mage::stoneSkinCase(){
    this->health += 5;
    if (this->health > 100) this->health = 100; //no se puede curar mas del maximo de vida.
}

void Mage::magicSilenceCase(){
    this->magicBuff = 0; //no puede usar magia.
}

void Mage::elementalExposureCase(){
    exposed = true;
}

void Mage::manaLeechCase(){
    this->mana -= 5;
    if (this->mana < 0) this->mana = 0;
}