#ifndef MAGE_HPP
#define MAGE_HPP

#include "../character.hpp"

class Mage: public Character, public enable_shared_from_this<Mage> {
protected:
    string name;
    CharacterType type;
    int health;
    int maxHealth;
    int mana;
    int magicBuff;
    pair<unique_ptr<Weapon>, unique_ptr<Weapon>> weapons;
    int BASE_DAMAGE=10;

    //atributos para manejar efectos.
    vector<pair<Effect, int>> currentEffects;
    bool stunned = false;
    bool forcedCritical = false;
    bool opponentMiss = false;
    bool exposed = false;

    Mage(string name, CharacterType type, int maxHealth, int mana);
public:
    string getName() const override;
    int getHealth() const override;
    int getMaxHealth() const override;
    int getMana() const;
    int getBuff() const override;
    void receiveDamage(int dam) override;

    void heal(int amount) override;
    string getType() const override;

    void addWeapon(unique_ptr<Weapon> w) override;
    pair<unique_ptr<Weapon>, unique_ptr<Weapon>> inventory() override;
    string useWeapon(unique_ptr<Weapon> w, shared_ptr<Character> op, shared_ptr<Team> targetTeam) = 0;
    void loseWeapon(unique_ptr<Weapon>& weapon) override;
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
    void stoneSkinCase();
    void magicSilenceCase();
    void elementalExposureCase() override;
    void manaLeechCase();

    friend class Staff;
    friend class Potion;
    friend class Spellbook;
};

#endif // MAGE_HPP