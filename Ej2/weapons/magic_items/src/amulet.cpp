#include "../headers/amulet.hpp"

Amulet::Amulet(AmuletProp prop, shared_ptr<Character> holder): 
    Magic(3, false, 0), property(prop), active(false), cooldown(0){
        name = getType();
        this->holder = holder;
        if (holder) giveEffect();
}

string Amulet::getType() const {
    switch (property){
        case PROP_HEALING: return "Healing Amulet";
        case PROP_STRENGTH: return "Strength Amulet";
        case PROP_IMMUNITY: return "Immunity Amulet";
        case PROP_LUCK: return "Lucky Amulet";
        default: return "Unknown Amulet";
    }
}

void Amulet::setHolder(shared_ptr<Character> holder){
    this->holder = holder;
    giveEffect();
}

string Amulet::use(shared_ptr<Team>, shared_ptr<Character>, shared_ptr<Character>, int){
    if (this->cooldown) return holder->getName() + " can't use " + this->name + " yet!";
    switch (property){
        case PROP_HEALING: holder->applyEffect(REGENERATION, this->duration); break;
        case PROP_STRENGTH: holder->applyEffect(STRENGTH, this->duration); break;
        case PROP_IMMUNITY: holder->applyEffect(IMMUNITY, this->duration); break;
        case PROP_LUCK: holder->applyEffect(LUCK, this->duration); break;
    }
    return holder->getName() + " activated " + name + "!\n";
}

void Amulet::giveEffect(){
    if (active) return;
    switch (property){
        case PROP_HEALING: holder->applyEffect(REGENERATION, duration); break;
        case PROP_STRENGTH: holder->applyEffect(STRENGTH, duration); break;
        case PROP_IMMUNITY: holder->applyEffect(IMMUNITY, duration); break;
        case PROP_LUCK: holder->applyEffect(LUCK, duration); break;
    }
}
