#include "amulet.hpp"
#include "../../../characters/character.hpp"

Amulet::Amulet(AmuletProp prop, Character* holder): 
    Magic(3), property(prop), active(false), cooldown(0){
        name = getMaterial();
        holder = holder;
        if (holder) giveEffect();
}

string Amulet::getMaterial() const {
    switch (property){
        case PROP_HEALING: return "Healing Amulet";
        case PROP_STRENGTH: return "Strength Amulet";
        case PROP_IMMUNITY: return "Immunity Amulet";
        case PROP_LUCK: return "Lucky Amulet";
        case PROP_INVISIBILITY: return "Invisible Amulet";
        default: return "Unknown Amulet";
    }
}

void Amulet::setHolder(Character* holder){
    this->holder = holder;
    giveEffect();
}

void Amulet::use(){
    if (cooldown) {cout << "You must wait " << cooldown << " turns to use the amulet again." << endl; return;}
    active = !active;
}

void Amulet::giveEffect(){
    switch (property){
        case PROP_HEALING: holder->applyEffect(REGENERATION, durability); break;
        case PROP_STRENGTH: holder->applyEffect(STRENGTH, durability); break;
        case PROP_IMMUNITY: holder->applyEffect(IMMUNITY, durability); break;
        case PROP_LUCK: holder->applyEffect(LUCK, durability); break;
        case PROP_INVISIBILITY: holder->applyEffect(INVISIBILITY, durability); break;
    }
}