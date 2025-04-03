#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "../magic.hpp"
#include <vector>
#include <string>

class Spellbook : public Magic {
public:
    Spellbook(string name, int magicPower, int durability);

    int getWeight() const;
    void use();
    void castSpell(const string& spellName) override;
    int attack() override;

    void addSpell(const string& spellName);
    void removeSpell(const string& spellName);
    vector<string> listSpells() const;
    bool hasSpell(const string& spellName) const;

private:
    vector<string> spells;
};

#endif // SPELLBOOK_HPP