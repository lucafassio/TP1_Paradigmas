#include "warrior.hpp"
#include "../mages/warlock/warlock.hpp"

// Combat weapons and base
#include "../../weapons/combat_weapons/sword/sword.hpp"
#include "../../weapons/combat_weapons/axe/axe.hpp"
#include "../../weapons/combat_weapons/spear/spear.hpp"
#include "../../weapons/combat_weapons/basto/basto.hpp"
#include "../../weapons/combat_weapons/double_axe/double_axe.hpp"

// Magic items
#include "../../weapons/magic_items/amulet/amulet.hpp"
#include "../../weapons/magic_items/potion/potion.hpp"
#include "../../weapons/magic_items/spellbook/spellbook.hpp"
#include "../../weapons/magic_items/staff/staff.hpp"

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
    if (opponentMiss){
        cout << name << " dodges the attack!" << endl;
        opponentMiss = false;
        return;
    }
    if (exposed) dam = static_cast<int>(dam * 1.3); //el daño se multiplica por 1.3 si el guerrero esta expuesto.
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

void Warrior::addWeapon(unique_ptr<Weapon> w) {
    if (!weapons.first) weapons.first = move(w);
    else if (!weapons.second) weapons.second = move(w);
    else cout << "Both weapon slots are occupied." << endl;
}

pair<unique_ptr<Weapon>, unique_ptr<Weapon>> Warrior::inventory(){
    unique_ptr<Weapon> weaponsCopy1 = nullptr;
    unique_ptr<Weapon> weaponsCopy2 = nullptr;
    if (auto castedWeapon = dynamic_cast<Axe*>(weapons.first.get())) weaponsCopy1 = make_unique<Axe>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Basto*>(weapons.first.get())) weaponsCopy1 = make_unique<Basto>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<DoubleAxe*>(weapons.first.get())) weaponsCopy1 = make_unique<DoubleAxe>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Spear*>(weapons.first.get())) weaponsCopy1 = make_unique<Spear>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Sword*>(weapons.first.get())) weaponsCopy1 = make_unique<Sword>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Amulet*>(weapons.first.get())) weaponsCopy1 = make_unique<Amulet>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Potion*>(weapons.first.get())) weaponsCopy1 = make_unique<Potion>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Spellbook*>(weapons.first.get())) weaponsCopy1 = make_unique<Spellbook>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Staff*>(weapons.first.get())) weaponsCopy1 = make_unique<Staff>(*castedWeapon);

    if (auto castedWeapon = dynamic_cast<Axe*>(weapons.second.get())) weaponsCopy2 = make_unique<Axe>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Basto*>(weapons.second.get())) weaponsCopy2 = make_unique<Basto>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<DoubleAxe*>(weapons.second.get())) weaponsCopy2 = make_unique<DoubleAxe>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Spear*>(weapons.second.get())) weaponsCopy2 = make_unique<Spear>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Sword*>(weapons.second.get())) weaponsCopy2 = make_unique<Sword>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Amulet*>(weapons.second.get())) weaponsCopy2 = make_unique<Amulet>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Potion*>(weapons.second.get())) weaponsCopy2 = make_unique<Potion>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Spellbook*>(weapons.second.get())) weaponsCopy2 = make_unique<Spellbook>(*castedWeapon);
    else if (auto castedWeapon = dynamic_cast<Staff*>(weapons.second.get())) weaponsCopy2 = make_unique<Staff>(*castedWeapon);

    return {move(weaponsCopy1), move(weaponsCopy2)};
}

void Warrior::loseWeapon(unique_ptr<Weapon>& weapon) {
    if (weapons.first && weapons.first.get() == weapon.get()) weapons.first.reset();
    else if (weapons.second && weapons.second.get() == weapon.get()) weapons.second.reset();
    else cout << "Weapon not found in inventory." << endl;
}

void Warrior::endTurnUpdate() {
    this->effectUpdate();
}

string Warrior::warlockSoulLink(shared_ptr<Character> target, shared_ptr<Team> targetTeam, int finalDamage) {
    string logText;
    shared_ptr<Warlock> opponentWarlock = targetTeam->getWarlock();

    if (target->hasEffect(SOUL_LINKED) && opponentWarlock->linkedAllies.size()) {
        logText += " dealing " + to_string(finalDamage) + " damage to all linked allies!\n";
        int nAlives = static_cast<int>(opponentWarlock->linkedAllies.size());

        for (auto it = opponentWarlock->linkedAllies.begin(); it != opponentWarlock->linkedAllies.end(); it++) {
            auto opponent = *it;

            //me lo guardo para handelear el caso de que Mercenary se escape.
            string name = opponent->getName();

            //el daño total se reparte equitativamente entre los aliados enlazados.
            opponent->receiveDamage(finalDamage / nAlives);

            //me fijo si no se fue el Mercenary.
            if (!targetTeam->getMember(name)) {
                logText += name + " has escaped.\n";
                it = opponentWarlock->linkedAllies.erase(it);
                it--;
            }

            logText += opponent->getName() + " (" + opponent->getType() + ") receives " + to_string(finalDamage / nAlives) + " damage from Soul Link!\n";

            // si un oponente muere, se corta su vínculo.
            if (!opponent->getHealth()) {
                it = opponentWarlock->linkedAllies.erase(it);
                it--;
            }
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
void Warrior::applyEffect(Effect effect, int duration){
    if (hasEffect(effect)){
        for (auto it = currentEffects.begin(); it != currentEffects.end(); it++)
            if (it->first == effect) it->second += duration;
    }
    else currentEffects.push_back(make_pair(effect, duration));
}

vector<pair<Effect, int>> Warrior::getCurrentEffects() const {
    return currentEffects;
}

bool Warrior::hasEffect(Effect effect) const {
    for (auto& e : currentEffects) {
        if (e.first == effect && e.second) return true;
    }
    return false;
}

void Warrior::effectUpdate(){
    if (this->currentEffects.empty()) return;
    for (auto effect = this->currentEffects.begin(); effect != this->currentEffects.end();){
        if (!effect->second){
            effect = this->currentEffects.erase(effect);
            if (effect == this->currentEffects.end()) return; //si borro el ultimo efecto, salgo.
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
                case FREEZING: this->freezingCase(); break;
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
    if (!hasEffect(IMMUNITY)) health -= 5;
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

void Warrior::freezingCase(){
    stunned = true; //el proximo turno no puede atacar.
}

void Warrior::elementalExposureCase(){
    exposed = true; //el proximo ataque del oponente sera un critico.
}