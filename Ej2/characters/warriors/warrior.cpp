#include "warrior.hpp"
#include "../../../Ej3/team.hpp"
#include "../mages/warlock/warlock.hpp"

Warrior::Warrior(string name, CharacterType type, int maxHealth, int armor):
    name(name), type(type), health(100), maxHealth(maxHealth), armor(armor), combatBuff(2), weapons(nullptr, nullptr)
{}

string Warrior::getName() const {
    return name;
}

int Warrior::getHealth() const {
    return health;
}

int Warrior::getMaxHealth() const {
    return maxHealth;
}

int Warrior::getArmor() const {
    return armor;
}

int Warrior::getBuff() const {
    return combatBuff;
}

void Warrior::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth; //no se puede curar mas del maximo de vida.
}

void Warrior::receiveDamage(int dam){
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

void Warrior::addWeapon(shared_ptr<Weapon> w){
    if (weapons.first == nullptr) weapons.first = w;
    else if (weapons.second == nullptr) weapons.second = w;
}

pair<shared_ptr<Weapon>, shared_ptr<Weapon>> Warrior::inventory() const {
    return weapons;
}

void Warrior::loseWeapon(shared_ptr<Weapon> weapon){
    if (weapons.first == weapon) weapons.first = nullptr;
    else if (weapons.second == weapon) weapons.second = nullptr;
    else cout << "Weapon not found in inventory." << endl;
}

void Warrior::endTurnUpdate(){
    this->effectUpdate();
}

void Warrior::warlockSoulLink(shared_ptr<Character> target, shared_ptr<Team> targetTeam, int finalDamage){
    shared_ptr<Warlock> opponentWarlock = targetTeam->getWarlock();
    if (target->hasEffect(SOUL_LINKED) && opponentWarlock->linkedAllies.size()){
        cout << " dealing " << finalDamage << " damage to all linked allies!" << endl;
        int nAlives = static_cast<int>(opponentWarlock->linkedAllies.size());
        for (auto it = opponentWarlock->linkedAllies.begin(); it != opponentWarlock->linkedAllies.end(); it++){
            auto opponent = *it;

            //me lo guardo para handelear el caso de que Mercenary se escape.
            string name = opponent->getName();

            //el daño total se reparte equitativamente entre los aliados enlazados.
            opponent->receiveDamage(finalDamage / nAlives);

            //me fijo si no se fue el Mercenary.
            if (!targetTeam->getMember(name)){
                cout << "se fue." << endl;
                it = opponentWarlock->linkedAllies.erase(it);
                it--;
            }
            cout << opponent->getName() << " (" << opponent->getType() << ") receives " << finalDamage / nAlives << " damage from Soul Link!" << endl;

            // si un oponente muere, se corta su vínculo.
            if (!opponent->getHealth()){
                it = opponentWarlock->linkedAllies.erase(it);
                it--;
            }
        }
        if (!opponentWarlock->getHealth()) opponentWarlock->breakSoulLink();
    }
    else{
        //aplicar daño al oponente.
        cout << " and deals " << finalDamage << " damage!" << endl;
        target->receiveDamage(finalDamage);
    }
}

// ======= METODOS PARA MANEJAR EFECTOS ======= //
void Warrior::applyEffect(Effect effect, int duration){
    currentEffects.push_back(make_pair(effect, duration));
}

bool Warrior::hasEffect(Effect effect) const {
    for (auto& e : currentEffects) {
        if (e.first == effect && e.second) return true;
    }
    return false;
}

void Warrior::effectUpdate(){
    for (auto effect = this->currentEffects.begin(); effect != this->currentEffects.end();){
        if (!effect->second){
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
                case STONE_SKIN: break; //no afecta a los warriors
                case MAGIC_SILENCE: break; //no afecta a los warriors
                case ELEMENTAL_EXPOSURE: this->elementalExposureCase(); break;
                case SOUL_LINKED: break; //no se aplica aca.
                case MANA_LEECH: break; //no afectan a los warriors.
                case SCARED: break; //no se aplica aca.
                case RAGE: break; //no se aplica aca.
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

void Warrior::burnCase(){
    if (!!hasEffect(IMMUNITY)) health -= 5;
    if (health < 0) health = 0;
}

void Warrior::bleedCase(){
    health -= 5;
    if (health < 0) health = 0;
}

void Warrior::poisonCase(){
    if (!hasEffect(IMMUNITY)) health -= 5;
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

void Warrior::invisibilityCase(){
    opponentMiss = true;
}

void Warrior::frozenCase(){
    stunned = true; //el proximo turno no puede atacar.
}

void Warrior::elementalExposureCase(){
    exposed = true; //el proximo ataque del oponente sera un critico.
}