#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include "../character.hpp"

class Warrior: public Character, public enable_shared_from_this<Warrior> {
protected:
    string name;
    CharacterType type;
    int health;
    int maxHealth;
    int armor;
    int combatBuff;
    pair<shared_ptr<Weapon>, shared_ptr<Weapon>> weapons;
    int BASE_DAMAGE = 10;

    //atributos para manejar efectos.
    vector<pair<Effect, int>> currentEffects;
    bool stunned = false;
    bool forcedCritical = false;
    bool opponentMiss = false; 
    bool exposed = false;

    Warrior(string name, CharacterType type, int maxHealth, int armor);

public:
    string getName() const override;
    int getHealth() const override;
    int getMaxHealth() const override;
    int getArmor() const;
    int getBuff() const override;
    string getType() const override;

    void heal(int amount) override;
    void receiveDamage(int dam) override;

    void addWeapon(shared_ptr<Weapon> w) override;
    pair<shared_ptr<Weapon>, shared_ptr<Weapon>> inventory() const override;
    string useWeapon(shared_ptr<Weapon> weapon, shared_ptr<Character> target, shared_ptr<Team> targetTeam) = 0;
    void loseWeapon(shared_ptr<Weapon> weapon) override;
    void endTurnUpdate() override;

    string warlockSoulLink(shared_ptr<Character> target, shared_ptr<Team> targetTeam, int finalDamage) override;

    //metodos para manejar efectos.
    void applyEffect(Effect effect, int duration) override;
    vector<pair<Effect, int>> getCurrentEffects() const override;
    bool hasEffect(Effect effect) const override;
    void effectUpdate() override;
    void regenCase() override;
    void burnCase() override;
    void bleedCase() override;
    void poisonCase() override;
    void stunCase() override;
    void luckCase() override;
    void invisibilityCase() override;
    void freezingCase() override;
    void elementalExposureCase() override;

    friend class Staff;
    friend class Potion;
};

#endif // WARRIOR_HPP
