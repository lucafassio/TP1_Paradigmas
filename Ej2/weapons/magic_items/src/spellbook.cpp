#include "spellbook.hpp"
#include "../../../characters/mages/headers/conjurer.hpp"
#include "../../../characters/mages/headers/necromancer.hpp"
#include "../../../characters/mages/headers/sorcerer.hpp"
#include "../../../characters/mages/headers/warlock.hpp"

Spellbook::Spellbook(string name): 
    Magic(0, true, 0){
    spells = {"Fireball", "Ice Spike", "Clone Illusion", "Magic Seal", "Elemental Rupture"};
    this->name = name;
}

Spellbook::Spellbook(const Spellbook& other): 
    Magic(other.duration, other.reusable, other.cooldown){
    this->spells = other.spells;
    this->name = other.name;
}

string Spellbook::use(shared_ptr<Team> holderTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber){
    spellNumber--;
    if (dynamic_pointer_cast<Mage>(holder)){
        switch (static_cast<Spells>(spellNumber)){
            case FIREBALL:
                target->applyEffect(BURNING, 2);
                target->receiveDamage(10);
                return holder->getName() + " casts Fireball on " + target->getName() + ", causing burning!\n";
            case ICE_SPIKE:
                target->applyEffect(FREEZING, 1);
                target->receiveDamage(10);
                return holder->getName() + " casts Ice Spike on " + target->getName() + ", freezing him!\n";
            case CLONE_ILLUSION:
                this->addClone(holderTeam, holder);
                return holder->getName() + " casts Clone Illusion, creating a clone!\n";
            case MAGIC_SEAL:
                target->applyEffect(MAGIC_SILENCE, 3);
                return holder->getName() + " casts Magic Seal on " + target->getName() + ", silencing him!\n";
            case ELEMENTAL_RUPTURE:
                target->applyEffect(ELEMENTAL_EXPOSURE, 3);
                return holder->getName() + " casts Elemental Rupture on " + target->getName() + ", weakening him to damage!\n";
            default:
                return holder->getName() + " tries to cast an unknown spell!";
        }
    }
    else return holder->getName() + " doesnt know how to use this. " + holder->useWeapon(nullptr, target, holderTeam);
}

void Spellbook::addClone(shared_ptr<Team> holderTeam, shared_ptr<Character> holder) {
    shared_ptr<Mage> mageHolder = dynamic_pointer_cast<Mage>(holder);
    CharacterType cloneType = mageHolder->type;
    switch (cloneType){
        case CONJURER: holderTeam->members.push_back(make_shared<Conjurer>(holder->getName() + "'s Clone")); break;
        case NECRO: holderTeam->members.push_back(make_shared<Necromancer>(holder->getName() + "'s Clone")); break;
        case SORCERER: holderTeam->members.push_back(make_shared<Sorcerer>(holder->getName() + "'s Clone")); break;
        case WARLOCK: holderTeam->members.push_back(make_shared<Warlock>(holder->getName() + "'s Clone")); break;
        default: break; // No se puede crear un clon de un guerrero.
    }
}