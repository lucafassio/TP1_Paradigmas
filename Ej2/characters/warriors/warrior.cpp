#include "warrior.hpp"
#include "../../../Ej3/team.hpp"

void Warrior::setHealth(int health) {
    this->health = health;
}

Warrior::Warrior(string name, CharacterType type, int armor):
    name(name), type(type), health(100), armor(armor), combatBuff(2), weapons(nullptr, nullptr)
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

int Warrior::getBuff() const {
    return combatBuff;
}

void Warrior::heal(int amount) {
    health += amount;
    if (health > 100) health = 100; //no se puede curar mas del maximo de vida.
}

void Warrior::receiveDamage(int dam){
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

int Warrior::useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam){
    if (!targetTeam) return 0;
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

    if ((target->getType() == "Barbarian" || target->getType() == "Gladiator") && rand() % 100 < 20){
        //los barbaros y gladiadores tienen un 20% de chance de contraatacar haciendo un 40% menos de daño.
        this->receiveDamage(weaponDamage * 0.6);
        cout << target->getName() << " (" << target->getType() << ") counterattacks!" << endl;
    }

    return weaponDamage;
}

void Warrior::loseWeapon(shared_ptr<Weapon> weapon){
    if (weapons.first == weapon) weapons.first = nullptr;
    else if (weapons.second == weapon) weapons.second = nullptr;
    else cout << "Weapon not found in inventory." << endl;
}

void Warrior::endTurnUpdate(shared_ptr<Team> currentTeam){
    this->effectUpdate(currentTeam);
    if (!this->health) currentTeam->loseMember(shared_from_this());
}

// ======= METODOS PARA MANEJAR EFECTOS ======= //
void Warrior::applyEffect(Effect effect, int duration){
    currentEffects.push_back(make_pair(effect, duration));
}

bool Warrior::hasEffect(Effect effect) const {
    for (auto& e : currentEffects) {
        if (e.first == effect) return true;
    }
    return false;
}

void Warrior::effectUpdate(shared_ptr<Team> currentTeam){
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
                case FROZEN: this->frozenCase(); break;
                case STONE_SKIN: break; //no afecta a los warriors
                case MAGIC_SILENCE: break; //no afecta a los warriors
                case ELEMENTAL_EXPOSURE: this->elementalExposureCase(); break;
                case SOUL_LINKED: break; //no se aplica aca.
                case MANA_LEECH: break; //no afectan a los warriors.
            }
            if (!this->health) currentTeam->loseMember(shared_from_this());
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
    if (!immune) health -= 5;
    if (health < 0) health = 0;
}

void Warrior::bleedCase(){
    health -= 5;
    if (health < 0) health = 0;
}

void Warrior::poisonCase(){
    if (!immune) health -= 5;
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

void Warrior::frozenCase(){
    stunned = true; //el proximo turno no puede atacar.
}

void Warrior::elementalExposureCase(){
    exposed = true; //el proximo ataque del oponente sera un critico.
}