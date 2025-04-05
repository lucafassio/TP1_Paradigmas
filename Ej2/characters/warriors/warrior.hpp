#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include "../character.hpp"
#include "../../weapons/weapon.hpp"

class Warrior : public Character{
protected:
    string name;
    CharacterType type;
    int health;
    int armor;
    int combatBuff;
    pair<Weapon*, Weapon*> weapons;
    int BASE_DAMAGE=10;

    //atributos para manejar efectos.
    vector<pair<Effect, int>> currentEffects;
    bool strengthBuff = false;
    bool immune = false;
    bool stunned = false;
    bool forcedCritical = false;
    bool opponentMiss = false; 

public:
    Warrior(string name, CharacterType type, int health, int armor);

    string getName() const override;
    int getHealth() const override;
    int getArmor() const;
    int getBuff() const override;
    string getType() const override;

    void heal(int amount) override;
    void reciveDamage(int dam) override;

    void addWeapon(Weapon *w) override;
    pair<Weapon*, Weapon*> inventory() const override;
    int useWeapon(Weapon* weapon, Character* target, Team* targetTeam) override;
    void loseWeapon(Weapon* weapon) override;

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

#endif // WARRIOR_HPP
