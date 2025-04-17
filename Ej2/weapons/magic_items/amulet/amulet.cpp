#include "amulet.hpp"

Amulet::Amulet(AmuletProp prop): 
    Magic(3, true, 0), property(prop)
{name = getType();}

Amulet::Amulet(const Amulet& other):
    Magic(other.duration, other.reusable, other.cooldown), property(other.property)
{name = other.name;}

string Amulet::getType() const {
    switch (property){
        case PROP_HEALING: return "Healing Amulet";
        case PROP_STRENGTH: return "Strength Amulet";
        case PROP_IMMUNITY: return "Immunity Amulet";
        case PROP_LUCK: return "Lucky Amulet";
        default: return "Unknown Amulet";
    }
}

string Amulet::use(shared_ptr<Team>, shared_ptr<Character> holder, shared_ptr<Character>, int){
    if (this->cooldown) return holder->getName() + " can't use " + this->name + " yet!";
    switch (property){
        case PROP_HEALING: holder->applyEffect(REGENERATION, this->duration); break;
        case PROP_STRENGTH: holder->applyEffect(STRENGTH, this->duration); break;
        case PROP_IMMUNITY: holder->applyEffect(IMMUNITY, this->duration); break;
        case PROP_LUCK: holder->applyEffect(LUCK, this->duration); break;
    }
    return holder->getName() + " activated " + name + "!\n";
}
