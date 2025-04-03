#include "team.hpp"

Team::Team(int num): members() {} // Initialize empty vector

Character* Team::getMember(string name) const {
    for (auto& member : members) {
        if (member && member->getName() == name) {  // Check if member is not null
            return member;
        }
    }
    cout << "Character " << name << " not found in team" << endl;  // Add error message
    return nullptr;
}
