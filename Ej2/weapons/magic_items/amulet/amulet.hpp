#ifndef AMULET_HPP
#define AMULET_HPP

#include "../magic.hpp"

class Character;

class Amulet final : public Magic{
    private:
        AmuletProp property;
        bool active;
        int cooldown;
        shared_ptr<Character> holder;

    public:
        Amulet(AmuletProp prop, shared_ptr<Character> holder);
        
        string getMaterial() const override;

        void setHolder(shared_ptr<Character> holder);

        void use();
        void giveEffect();
    
};

#endif // AMULET_HPP
