#ifndef POTION_HPP
#define POTION_HPP

#include "magic.hpp"
#include <string>
#include <iostream>
using namespace std;

class Potion final : public Magic {
private:
    string type;
    bool expired;

public:
    Potion(const string& name, int magicPower, int durability, const string& type, bool expired);

    int getWeight() const override;
    void use() override;
    void castSpell(const string& spellName) override;

    // Additional methods
    string getType() const;
    bool isExpired() const;
    void increasePotency(int amount);
    void decreasePotency(int amount);
};

#endif // POTION_HPP
