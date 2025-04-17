#include "magic.hpp"

Magic::Magic(int duration, bool reusable, int cooldown): 
    duration(duration), reusable(reusable), cooldown(cooldown)
{}

string Magic::getName() const {
    return name;
}

bool Magic::isCombat() const {
    return false;
}

int Magic::getDuration() const {
    return duration;
}

int Magic::attack(){
    return 0;
}

void Magic::decreaseCooldown(){
    if (cooldown > 0) cooldown--;
}