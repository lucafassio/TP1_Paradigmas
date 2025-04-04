#include "staff.hpp"

Staff::Staff(string name, int durability): 
    Magic(durability){
        this->name = name;
}

string Staff::getMaterial() const {
    return name;
}

void Staff::use() {
    cout << "Using " << name << "!" << endl;
    // Implement staff-specific magic effects here
}