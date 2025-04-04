#ifndef AMULET_HPP
#define AMULET_HPP

#include "../magic.hpp"

class Character;

enum AmuletProp{
    PROP_HEALING,
    PROP_STRENGTH,
    PROP_IMMUNITY,
    PROP_LUCK,
    PROP_INVISIBILITY
};

class Amulet final : public Magic{
    private:
        AmuletProp property;
        bool active;
        int cooldown;
        Character* holder;

    public:
        Amulet(AmuletProp prop, Character* holder);
        
        string getMaterial() const override;

        void setHolder(Character* holder);

        void use();
        void giveEffect();
        void update(Character* target);
    
};

#endif // AMULET_HPP
