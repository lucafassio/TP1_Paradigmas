#include "team.hpp"
#include "../Ej2/characters/character.hpp"
#include "../Ej2/characters/mages/warlock/warlock.hpp"

Team::Team(string name): 
    name(name), members()
{}

string Team::getName() const {
    return name;
}

vector<shared_ptr<Character>> Team::getMembers() const {
    return members;
}

shared_ptr<Character> Team::getMember(string name) const {
    for (auto& member : members)
        if (member->getName() == name) return member;
    cout << "Character " << name << " not found in team" << endl;
    return nullptr;
}

shared_ptr<Warlock> Team::getWarlock() const {
    for (auto& m : members)
        if (m->getType() == "Warlock") return static_pointer_cast<Warlock>(m);
    return nullptr;
}

void Team::loseMember(shared_ptr<Character> member){
    auto it = remove(members.begin(), members.end(), member);
    if (it != members.end()) members.erase(it, members.end());
    else cout << "Character not found in team" << endl;
}

void Team::showMembers() const {
    cout << name << " members:" << endl;
    for (const auto& member : members)
        if (member) cout << member->getName() << " (" << member->getType() << ")" << endl;
}

void Team::sortMembersByType() {
    vector<string> typeOrder = {
        "Barbarian", "Gladiator", "Paladin", "Knight",
        "Conjurer", "Sorcerer", "Warlock", "Necromancer", "Mercenary"
    };

    auto getTypePriority = [&typeOrder](const string& type) {
        auto it = find(typeOrder.begin(), typeOrder.end(), type);
        return it != typeOrder.end() ? distance(typeOrder.begin(), it) : typeOrder.size();
    };

    sort(members.begin(), members.end(), [&getTypePriority](const shared_ptr<Character>& a, const shared_ptr<Character>& b) {
        return getTypePriority(a->getType()) < getTypePriority(b->getType());
    });
}