#ifndef FACTORY_HPP
#define FACTORY_HPP

//enums data
#include "../../utils/data.hpp"

//no me gustaba el nombre PersonajeFactory, lo cambie a Factory porque tambien hace armas.
class Factory{
    private:
        Factory() = delete;

    public:
        static shared_ptr<Character> createCharacter(CharacterType type, string name);
        static void addCharacterToTeam(shared_ptr<Team> team, shared_ptr<Character> character);
        static shared_ptr<Weapon> createWeapon(WeaponType type, Material mat);
        static shared_ptr<Weapon> createWeapon(WeaponType type, AmuletProp prop);
        static shared_ptr<Weapon> createWeapon(WeaponType type, PotionType pType);
        template<typename T, typename... Args>
        static shared_ptr<T> createWeapon(Args&&... args);
        static void addWeaponToCharacter(shared_ptr<Character> character, shared_ptr<Weapon> weapon);
};

#endif // FACTORY_HPP