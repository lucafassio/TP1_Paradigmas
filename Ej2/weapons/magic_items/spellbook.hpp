#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "magic.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Spellbook final : public Magic {
private:
    vector<string> spells;

public:
    Spellbook(const string& name, int magicPower, int durability);

    int getWeight() const override;
    void use() override;
    void castSpell(const string& spellName) override;

    // Additional methods
    void addSpell(const string& spellName);
    void removeSpell(const string& spellName);
    vector<string> listSpells() const;
    bool hasSpell(const string& spellName) const;
};

#endif // SPELLBOOK_HPP
