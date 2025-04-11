// #include "elementals.hpp"

// //====== MAGO DE FUEGO ======//
// FireSorcerer::FireSorcerer(string name): 
//     Sorcerer(name) 
// {}

// void FireSorcerer::attack(shared_ptr<Character> enemy){
//     enemy->applyEffect(BURNING, 2);
// }

// void FireSorcerer::special(shared_ptr<Character> enemy, shared_ptr<Team>){
//     enemy->applyEffect(ELEMENTAL_EXPOSURE, 3);
//     resetCooldown();
// }

// //====== MAGO DE AGUA ======//
// WaterSorcerer::WaterSorcerer(string name): 
//     Sorcerer(name) 
// {}

// void WaterSorcerer::attack(shared_ptr<Character> enemy) {
//     enemy->applyEffect(FROZEN, 1);
// }

// void WaterSorcerer::special(shared_ptr<Character> enemy, shared_ptr<Team>){
//     enemy->applyEffect(MAGIC_SILENCE, 2);
//     resetCooldown();
// }

// //====== MAGO DE AIRE ======//
// AirSorcerer::AirSorcerer(string name): 
//     Sorcerer(name) 
// {}

// void AirSorcerer::attack(shared_ptr<Character> enemy) {
//     enemy->applyEffect(STUN, 1);
// }

// void AirSorcerer::special(shared_ptr<Character> enemy, shared_ptr<Team>) {
//     enemy->applyEffect(POISON, 3);
//     resetCooldown();
// }

// //====== MAGO DE TIERRA ======//
// EarthSorcerer::EarthSorcerer(string name): 
//     Sorcerer(name) 
// {}

// void EarthSorcerer::attack(shared_ptr<Character> enemy) {
//     enemy->applyEffect(STONE_SKIN, 2);
// }

// void EarthSorcerer::special(shared_ptr<Character>, shared_ptr<Team> enemyTeam) {
//     for (const auto& c : enemyTeam->getMembers()) {
//         c->applyEffect(STONE_SKIN, 2);
//     }
//     resetCooldown();
// }