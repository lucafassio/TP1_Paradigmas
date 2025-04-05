#include "team.hpp"

Team::Team(): members() {} // Initialize empty vector

Character* Team::getMember(string name) const {
    for (auto& member : members) {
        if (member && member->getName() == name) {  // Check if member is not null
            return member;
        }
    }
    cout << "Character " << name << " not found in team" << endl;  // Add error message
    return nullptr;
}

void Team::loseMember(Character* member) {
    auto it = std::remove(members.begin(), members.end(), member);
    if (it != members.end()) {
        members.erase(it, members.end());
        delete member;  // Free the memory of the removed character
    } else {
        cout << "Character not found in team" << endl;  // Add error message
    }
}

void Team::showMembers() const {
    cout << "Team members:" << endl;
    for (const auto& member : members)
        if (member) cout << member->getName() << " (" << member->getType() << ")" << endl;
}