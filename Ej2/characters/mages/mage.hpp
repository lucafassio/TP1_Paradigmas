#ifndef MAGE_HPP
#define MAGE_HPP

#include "../character.hpp"

class Mage : public Character{
protected:
    string name;
    CharacterType type;
    int health;
    int mana;
    int magicPower;
    int spellSlots;
    pair<Weapon*, Weapon*> weapons;

    //atributos para manejar efectos.
    vector<pair<Effect, int>> currentEffects;
    bool strengthBuff = false;
    bool immune = false;
    bool stunned = false;
    bool forcedCritical = false;
    bool opponentMiss = false; 

public:
    Mage(string name);
    virtual ~Mage() = default;

    // Character interface implementation
    string getName() const override;
    int getHealth() const override;
    int getMana() const;
    int getBuff() const override;
    void reciveDamage(int dam) override;
    void addWeapon(Weapon* w) override;
    pair<Weapon*, Weapon*> inventory() const override;
    int useWeapon(Weapon* w, Character* op) override;

    // Mage specific methods
    virtual void castSpell(const string& spellName);
    int getMagicPower() const;
    int getSpellSlots() const;

    string getType() const override;
    void heal(int amount) override;
    
    //metodos para manejar efectos.
    void applyEffect(Effect effect, int duration) override;
    void effectUpdate() override;
    void regenCase();
    void strengthCase();
    void burnCase();
    void poisonCase();
    void stunCase();
    void luckCase();
    void immunityCase();
    void invisibilityCase();
};

#endif // MAGE_HPP