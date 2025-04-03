#ifndef POTION_HPP
#define POTION_HPP

#include "../magic.hpp"

class Potion : public Magic {
public:
    Potion(const string& name, int magicPower, int durability, const string& type, bool expired);

    int getWeight() const;
    void use();
    void castSpell(const string& spellName) override;
    int attack() override;

    string getType() const;
    bool isExpired() const;
    void increasePotency(int amount);
    void decreasePotency(int amount);

private:
    string type;
    bool expired;
};

#endif // POTION_HPP