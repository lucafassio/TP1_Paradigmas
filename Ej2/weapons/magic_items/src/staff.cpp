#include "../headers/staff.hpp"
#include "../../../characters/warriors/warrior.hpp"
#include "../../../characters/mages/mage.hpp"

Staff::Staff(string name):
    Magic(0, true, 0)
{name=name;}

Staff::Staff(const Staff& other):
    Magic(other.duration, other.reusable, other.cooldown){
    this->lastTurnMove = other.lastTurnMove;
    this->echoCooldown = other.echoCooldown;
}

void Staff::setEcho(vector<int> lastTurnMove) {
    this->lastTurnMove = lastTurnMove;
}

vector<int> Staff::getEcho(){
    vector<int> lastTurnMoveCopy = lastTurnMove;
    lastTurnMove.clear();
    return lastTurnMoveCopy;
}

string Staff::use(shared_ptr<Team> targetTeam, shared_ptr<Character> holder, shared_ptr<Character> target, int spellNumber){
    switch (spellNumber){
        case 1: return holder->getName() + " casts Storm Chain, chaining " + stormChain(targetTeam, target);
        case 2:
            mysticEcho();
            return holder->getName() + " casts Mystic Echo!";
        case 3:
            staffOfEchoes(targetTeam, holder);
            return holder->getName() + " casts Staff of Echoes, supporting allies!";
        case 4:
            chaoticFlare(targetTeam, holder);
            return holder->getName() + " casts Chaotic Flare, causing damage and burns!";
        default: 
            return holder->getName() + " tries to cast an unknown spell!";
    }
}

string Staff::stormChain(shared_ptr<Team> targetTeam, shared_ptr<Character> mainTarget){
    int secureCounter = 0;
    int randomNumber = rand() % static_cast<int>(targetTeam->getMembers().size());
    auto chainFirstJump = targetTeam->getMembers().at(randomNumber);
    while (!chainFirstJump->getHealth() || chainFirstJump == mainTarget){
        chainFirstJump = targetTeam->getMembers().at(++randomNumber % static_cast<int>(targetTeam->getMembers().size()));
        secureCounter++;
        if (secureCounter > static_cast<int>(targetTeam->getMembers().size()) + 2) break;
    }
    secureCounter = 0;
    auto chainSecondJump = targetTeam->getMembers().at(randomNumber);
    while (!chainSecondJump->getHealth() || chainSecondJump == mainTarget || chainSecondJump == chainFirstJump){
        chainSecondJump = targetTeam->getMembers().at(++randomNumber % static_cast<int>(targetTeam->getMembers().size()));
        secureCounter++;
        if (secureCounter > static_cast<int>(targetTeam->getMembers().size()) + 2) break;
    }

    mainTarget->receiveDamage(20);
    chainFirstJump->receiveDamage(10);
    chainSecondJump->receiveDamage(5);

    return "20 damage to " + mainTarget->getName() + ", 10 damage to " + chainFirstJump->getName() + ", and 5 damage to " + chainSecondJump->getName() + ".";
}

void Staff::mysticEcho(){
    if (this->echoCooldown > 0) return;
    this->echoCooldown = 2;
}

string Staff::staffOfEchoes(shared_ptr<Team> currentTeam, shared_ptr<Character> holder){
    shared_ptr<Character> ally = currentTeam->getMembers().at(0);

    for (const auto& member : currentTeam->getMembers())
        if (member->getHealth() < ally->getHealth() && member->getHealth()) ally = member;

    ally->heal(25);
    ally->applyEffect(REGENERATION, 3);

    if (dynamic_pointer_cast<Warrior>(ally)) dynamic_pointer_cast<Warrior>(ally)->combatBuff += 10;
    else if (dynamic_pointer_cast<Mage>(ally)) dynamic_pointer_cast<Mage>(ally)->mana += 30;

    return holder->getName() + " casts Staff of Echoes, healing " + ally->getName() + " for 25 health and applying regeneration!";
}

string Staff::chaoticFlare(shared_ptr<Team> targetTeam, shared_ptr<Character> holder){
    set<int> randomNumbers;
    while (randomNumbers.size() < 5){
        int randomNumber = rand() % static_cast<int>(targetTeam->getMembers().size());
        if (targetTeam->getMembers().at(randomNumber)->getHealth()) randomNumbers.insert(randomNumber);
    }
    for (const auto& randomNumber : randomNumbers){
        shared_ptr<Character> target = targetTeam->getMembers().at(randomNumber);
        if (rand() % 2) target->receiveDamage(15);
        else target->applyEffect(BURNING, 2);
    }
    return holder->getName() + " casts Chaotic Flare, dealing damage and applying burning to 5 random enemies!";
}