#ifndef MAGE_HPP
#define MAGE_HPP

#include "../character.hpp"
#include "../../weapons/weapon.hpp"
#include <memory>

class Mage : public Character{
protected:
    string name;
    CharacterType type;
    int health;
    int mana;
    int magicBuff;
    pair<shared_ptr<Weapon>, shared_ptr<Weapon>> weapons;
    int BASE_DAMAGE=10;

    //atributos para manejar efectos.
    vector<pair<Effect, int>> currentEffects;
    bool strengthBuff = false;
    bool immune = false;
    bool stunned = false;
    bool forcedCritical = false;
    bool opponentMiss = false;

public:
    Mage(string name, CharacterType type, int health, int mana);

    string getName() const override;
    int getHealth() const override;
    int getMana() const;
    int getBuff() const override;
    void reciveDamage(int dam) override;

    void heal(int amount) override;
    string getType() const override;

    void addWeapon(shared_ptr<Weapon> w) override;
    pair<shared_ptr<Weapon>, shared_ptr<Weapon>> inventory() const override;
    int useWeapon(shared_ptr<Weapon> w, shared_ptr<Character> op, shared_ptr<Team> targetTeam) override;
    void loseWeapon(shared_ptr<Weapon> weapon) override;
    
    //metodos para manejar efectos.
    void applyEffect(Effect effect, int duration) override;
    void effectUpdate() override;
    void regenCase() override;
    void strengthCase() override;
    void burnCase() override;
    void poisonCase() override;
    void stunCase() override;
    void luckCase() override;
    void immunityCase() override;
    void invisibilityCase() override;
};

#endif // MAGE_HPP