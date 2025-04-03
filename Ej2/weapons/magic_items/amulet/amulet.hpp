#ifndef AMULET_HPP
#define AMULET_HPP

#include "../magic.hpp"
#include <string>
#include <iostream>
using namespace std;

enum AmuletProp{
    HEALING,
    FIRE,
    INMUNITY
};

class Amulet final : public Magic {
private:
    AmuletProp property;
    bool active;

public:
    Amulet(AmuletProp prop);

    int getWeight() const;
    void use();
    void castSpell(const string& spellName) override;
    int attack() override;  // Add this line
    string getMaterial() const override;

    // Additional methods
    void activate();
    void deactivate();
    string getProperty() const;
    void setProperty(const string& newProperty);
};

#endif // AMULET_HPP
