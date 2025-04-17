#ifndef FACTORY_HPP
#define FACTORY_HPP

//enums data
#include "../utils/data.hpp"

//no me gustaba el nombre PersonajeFactory, lo cambie a Factory porque tambien hace armas.
class Factory{
    private:
        Factory() = delete;

    public:
        static shared_ptr<Character> createCharacter(CharacterType type, string name);
        static void addCharacterToTeam(shared_ptr<Team> team, shared_ptr<Character> character);
        static void createAndAddWeaponToCharacter(shared_ptr<Character> character, WeaponType type, Material mat);
        static void createAndAddWeaponToCharacter(shared_ptr<Character> character, WeaponType type, AmuletProp prop);
        static void createAndAddWeaponToCharacter(shared_ptr<Character> character, WeaponType type, PotionType effect);

};

#endif // FACTORY_HPP