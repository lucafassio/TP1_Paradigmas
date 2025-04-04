#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "../magic.hpp"

class Spellbook : public Magic {
private:
    string name;
    vector<string> spells;

public:
    Spellbook(string name, int durability);

    string getMaterial() const override;
    void use() override;
};

#endif // SPELLBOOK_HPP