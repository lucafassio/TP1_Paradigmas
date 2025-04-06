#include "../Ej2/characters/character.hpp"
#include "../Ej3/factory.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

//no lo agrego a enums_data porque solo se usa aca y es irrelevante para la funcionalidad de los personajes.
enum Attacks{
    FUERTE,
    RAPIDO,
    DEFENSA
}

int fight();