#include "potion.hpp"
#include "../../../characters/warriors/warrior.hpp"
#include "../../../characters/mages/mage.hpp"

Potion::Potion(PotionType type): 
    Magic(3, false, 0), type(type), thrown(false){
        name = getType();
}

Potion::Potion(const Potion& other):
    Magic(other.duration, other.reusable, other.cooldown), type(other.type){
        name = other.name;
}

string Potion::getType() const {
    switch (this->type){
        case MOLOTOV: return "Molotov"; break;
        case POTION_POISON: return "Poison Potion"; break;
        case POTION_STUN: return "Stun Potion"; break;
        case POTION_FROZEN: return "Frozen Potion"; break;
        case POTION_HEALING: return "Healing Potion"; break;
        case POTION_INVISIBILITY: return "Invisibility Potion"; break;
        default: return "Unknown Potion"; break;
    }
}

string Potion::use(shared_ptr<Team>, shared_ptr<Character> holder, shared_ptr<Character> target, int){
    if (thrown) return holder->getName() + " already used " + name + "!\n";
    switch (this->type){
        case MOLOTOV: target->applyEffect(BURNING, this->duration); break;
        case POTION_POISON: target->applyEffect(POISON, this->duration); break;
        case POTION_STUN: target->applyEffect(STUN, this->duration); break;
        case POTION_FROZEN: target->applyEffect(FREEZING, this->duration); break;
        case POTION_HEALING: target->applyEffect(REGENERATION, this->duration); break;
        case POTION_INVISIBILITY: target->applyEffect(INVISIBILITY, this->duration); break;
        default: cout << "Unknown potion type!" << endl; break;
    }
    thrown = true;
    return holder->getName() + " thrown " + name + " to " + target->getName() + "!\n";
}