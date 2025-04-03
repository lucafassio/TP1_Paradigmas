#ifndef MAGE_HPP
#define MAGE_HPP

#include "../character.hpp"
#include <vector>
#include <string>

class Mage : public Character {
protected:
    string name;
    int health;
    int mana;
    int magicPower;
    int spellSlots;
    pair<Weapon*, Weapon*> weapons;

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
    virtual void castSpell(const string& spellName) = 0;
    int getMagicPower() const;
    int getSpellSlots() const;
};

#endif // MAGE_HPP
