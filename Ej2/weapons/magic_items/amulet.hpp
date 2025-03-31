#ifndef AMULET_HPP
#define AMULET_HPP

#include "magic.hpp"
#include <string>
#include <iostream>
using namespace std;

class Amulet final : public Magic {
private:
    string property;
    bool active;

public:
    Amulet(const string& name, int magicPower, int durability, const string& property, bool active);

    int getWeight() const override;
    void use() override;
    void castSpell(const string& spellName) override;

    // Additional methods
    void activate();
    void deactivate();
    string getProperty() const;
    void setProperty(const string& newProperty);
};

#endif // AMULET_HPP
