#include "../../../Ej2/characters/character.hpp"
#include "../../../Ej2/characters/warriors/warrior.hpp"
#include "../../../Ej2/characters/mages/mage.hpp"
#include <algorithm>
#include <sstream>

string toUpperCase(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

string effectToString(Effect effect) {
    switch (effect) {
        case REGENERATION: return "Regeneration";
        case STRENGTH: return "Strength";
        case BURNING: return "Burning";
        case BLEEDING: return "Bleeding";
        case POISON: return "Poison";
        case STUN: return "Stun";
        case LUCK: return "Luck";
        case IMMUNITY: return "Immunity";
        case INVISIBILITY: return "Invisibility";
        case FREEZING: return "Frozen";
        case STONE_SKIN: return "Stone Skin";
        case MAGIC_SILENCE: return "Magic Silence";
        case ELEMENTAL_EXPOSURE: return "Elemental Exposure";
        case MANA_LEECH: return "Mana Leech";
        case SOUL_LINKED: return "Soul Linked";
        case SCARED: return "Scared";
        case RAGE: return "Rage";
        default: return "Unknown";
    }
}

string getHealthBar(int health, int maxHealth) {
    int filledBars = (health * 20) / maxHealth;
    int emptyBars = 20 - filledBars;

    ostringstream healthCounterStream;
    healthCounterStream << setw(4) << right << health << "/" << setw(4) << left << maxHealth;

    return "[" + string(filledBars, '#') + string(emptyBars, '_') + "] " + healthCounterStream.str();
}

string getManaBar(int mana, int maxMana) {
    int filledBars = (mana * 20) / maxMana;
    int emptyBars = 20 - filledBars;

    ostringstream manaCounterStream;
    manaCounterStream << setw(4) << right << mana << "/" << setw(4) << left << maxMana;

    return "[" + string(filledBars, '#') + string(emptyBars, '_') + "] " + manaCounterStream.str();
}

string getEmptyManaBar(){
    return "[" + string(20, '_') + "] " + "   0/0   ";
}

string getCombinedInventoryString(shared_ptr<Character> leftChar, shared_ptr<Character> rightChar) {
    auto leftInventory = leftChar->inventory();
    auto rightInventory = rightChar->inventory();

    string leftInventoryString = leftInventory.first || leftInventory.second ? "Inventory:" : "Inventory is empty.";
    string leftWeapons;
    if (leftInventory.first) {
        leftWeapons += leftInventory.first->getName();
    }
    if (leftInventory.second) {
        if (!leftWeapons.empty()) {
            leftWeapons += " - ";
        }
        leftWeapons += leftInventory.second->getName();
    }

    string rightInventoryString = rightInventory.first || rightInventory.second ? "Inventory:" : "Inventory is empty.";
    string rightWeapons;
    if (rightInventory.first) {
        rightWeapons += rightInventory.first->getName();
    }
    if (rightInventory.second) {
        if (!rightWeapons.empty()) {
            rightWeapons += " - ";
        }
        rightWeapons += rightInventory.second->getName();
    }

    int leftInventoryPadding = (70 - leftInventoryString.length()) / 2;
    int rightInventoryPadding = (70 - rightInventoryString.length()) / 2;

    int leftWeaponsPadding = (70 - leftWeapons.length()) / 2;
    int rightWeaponsPadding = (70 - rightWeapons.length()) / 2;

    ostringstream combinedInventoryStream;
    combinedInventoryStream << setfill(' ') 
                            << setw(leftInventoryPadding) << " " << leftInventoryString << setw(71 - leftInventoryPadding - leftInventoryString.length()) << "|"
                            << setw(rightInventoryPadding) << " " << rightInventoryString << setw(69 - rightInventoryPadding - rightInventoryString.length()) << "\n";
    combinedInventoryStream << setw(leftWeaponsPadding) << " " << leftWeapons << setw(71 - leftWeaponsPadding - leftWeapons.length()) << "|"
                            << setw(rightWeaponsPadding) << " " << rightWeapons << setw(69 - rightWeaponsPadding - rightWeapons.length());

    return combinedInventoryStream.str();
}

void showCharactersInfo(shared_ptr<Character> leftChar, shared_ptr<Character> rightChar) {
    string leftInfo = leftChar->getName() + " (" + leftChar->getType() + ")";
    string rightInfo = rightChar->getName() + " (" + rightChar->getType() + ")";
    
    int leftPadding = (70 - leftInfo.length()) / 2;
    int rightPadding = (70 - rightInfo.length()) / 2;
    cout << setfill(' ') << setw(leftPadding) << " " << leftInfo << setw(71 - leftPadding - leftInfo.length()) << "|";
    cout << setw(rightPadding) << " " << rightInfo << setw(69 - rightPadding - rightInfo.length()) << endl;

    string leftHealthBar = getHealthBar(leftChar->getHealth(), leftChar->getMaxHealth());
    string rightHealthBar = getHealthBar(rightChar->getHealth(), rightChar->getMaxHealth());
    int healthBarPadding = (70 - 22 - 9) / 2; // 22 is the fixed length of the health bar
    cout << setfill(' ') << setw(healthBarPadding) << " " << leftHealthBar
         << setw(71 - healthBarPadding - 22 - 10) << "|";
    cout << setw(healthBarPadding) << " " << rightHealthBar
         << setw(69 - healthBarPadding - 22 - 9) << endl;

    string leftIndicator = dynamic_pointer_cast<Mage>(leftChar) 
                           ? "Mana: " + to_string(dynamic_pointer_cast<Mage>(leftChar)->getMana()) + "/100" 
                           : "Armor: " + to_string(dynamic_pointer_cast<Warrior>(leftChar)->getArmor());
    string rightIndicator = dynamic_pointer_cast<Mage>(rightChar) 
                            ? "Mana: " + to_string(dynamic_pointer_cast<Mage>(rightChar)->getMana()) + "/100" 
                            : "Armor: " + to_string(dynamic_pointer_cast<Warrior>(rightChar)->getArmor());
    int leftIndicatorPadding = (70 - leftIndicator.length()) / 2;
    int rightIndicatorPadding = (70 - rightIndicator.length()) / 2;
    cout << setfill(' ') << setw(leftIndicatorPadding) << " " << leftIndicator << setw(71 - leftIndicatorPadding - leftIndicator.length()) << "|";
    cout << setw(rightIndicatorPadding) << " " << rightIndicator << setw(69 - rightIndicatorPadding - rightIndicator.length()) << endl;

    string combinedInventory = getCombinedInventoryString(leftChar, rightChar);

    cout << combinedInventory << endl;

    vector<pair<Effect, int>> leftEffects = leftChar->getCurrentEffects();
    vector<pair<Effect, int>> rightEffects = rightChar->getCurrentEffects();

    size_t maxEffects = max(leftEffects.size(), rightEffects.size());

    if (maxEffects > 0) {
        string effectsHeader = "Effects:";
        int leftEffectsHeaderPadding = (70 - effectsHeader.length()) / 2;
        int rightEffectsHeaderPadding = (70 - effectsHeader.length()) / 2;

        cout << setfill(' ') << setw(leftEffectsHeaderPadding) << " " << effectsHeader << setw(71 - leftEffectsHeaderPadding - effectsHeader.length()) << "|";
        cout << setw(rightEffectsHeaderPadding) << " " << effectsHeader << setw(69 - rightEffectsHeaderPadding - effectsHeader.length()) << endl;

        for (size_t i = 0; i < maxEffects; i++) {
            string leftEffectString = (i < leftEffects.size())
                                      ? effectToString(leftEffects[i].first) + ": " + to_string(leftEffects[i].second) + " turns"
                                      : "";
            string rightEffectString = (i < rightEffects.size())
                                       ? effectToString(rightEffects[i].first) + ": " + to_string(rightEffects[i].second) + " turns"
                                       : "";

            int leftEffectPadding = (70 - leftEffectString.length()) / 2;
            int rightEffectPadding = (70 - rightEffectString.length()) / 2;

            cout << setfill(' ') << setw(leftEffectPadding) << " " << leftEffectString << setw(71 - leftEffectPadding - leftEffectString.length()) << "|";
            cout << setw(rightEffectPadding) << " " << rightEffectString << setw(69 - rightEffectPadding - rightEffectString.length()) << endl;
        }
    }

    cout << setfill(' ') << setw(71) << "|" << endl;
    cout << setfill(' ') << setw(71) << "|" << endl;
    cout << setfill(' ') << setw(71) << "|" << endl;
}

void showSingleCharacterInfo(shared_ptr<Character> character, bool isLeft) {
    string characterInfo = character->getName() + " (" + character->getType() + ")";
    int padding = (70 - characterInfo.length()) / 2;

    if (isLeft) {
        cout << setfill(' ') << setw(padding) << " " << characterInfo << setw(71 - padding - characterInfo.length()) << "|";
        cout << setw(70) << " " << endl;
    } else {
        cout << setw(70) << " " << "|";
        cout << setfill(' ') << setw(padding) << " " << characterInfo << setw(69 - padding - characterInfo.length()) << endl;
    }

    string healthBar = getHealthBar(character->getHealth(), character->getMaxHealth());
    int healthBarPadding = (70 - 22) / 2;

    if (isLeft) {
        cout << setfill(' ') << setw(healthBarPadding - 5) << " " << healthBar
             << setw(71 - healthBarPadding - 22 - 5) << "|";
        cout << setw(70) << " " << endl;
    } else {
        cout << setw(70) << " " << "|";
        cout << setfill(' ') << setw(healthBarPadding - 5) << " " << healthBar
             << setw(69 - healthBarPadding - 22) << endl;
    }

    string indicator = dynamic_pointer_cast<Mage>(character)
                       ? "Mana: " + to_string(dynamic_pointer_cast<Mage>(character)->getMana()) + "/100"
                       : "Armor: " + to_string(dynamic_pointer_cast<Warrior>(character)->getArmor());
    int indicatorPadding = (70 - indicator.length()) / 2;

    if (isLeft) {
        cout << setfill(' ') << setw(indicatorPadding) << " " << indicator << setw(71 - indicatorPadding - indicator.length()) << "|";
        cout << setw(70) << " " << endl;
    } else {
        cout << setw(70) << " " << "|";
        cout << setfill(' ') << setw(indicatorPadding) << " " << indicator << setw(69 - indicatorPadding - indicator.length()) << endl;
    }

    auto inventory = character->inventory();
    string inventoryString = inventory.first || inventory.second ? "Inventory:" : "Inventory is empty.";
    string weapons;
    if (inventory.first) {
        weapons += inventory.first->getName();
    }
    if (inventory.second) {
        if (!weapons.empty()) {
            weapons += " - ";
        }
        weapons += inventory.second->getName();
    }

    int inventoryPadding = (70 - inventoryString.length()) / 2;
    int weaponsPadding = (70 - weapons.length()) / 2;

    if (isLeft) {
        cout << setfill(' ') << setw(inventoryPadding) << " " << inventoryString << setw(71 - inventoryPadding - inventoryString.length()) << "|";
        cout << setw(70) << " " << endl;
        cout << setfill(' ') << setw(weaponsPadding) << " " << weapons << setw(71 - weaponsPadding - weapons.length()) << "|";
        cout << setw(70) << " " << endl;
    } else {
        cout << setw(70) << " " << "|";
        cout << setfill(' ') << setw(inventoryPadding) << " " << inventoryString << setw(69 - inventoryPadding - inventoryString.length()) << endl;
        cout << setw(70) << " " << "|";
        cout << setfill(' ') << setw(weaponsPadding) << " " << weapons << setw(69 - weaponsPadding - weapons.length()) << endl;
    }

    if (!character->getCurrentEffects().empty()) {
        string effectsHeader = "Effects:";
        int effectsHeaderPadding = (70 - effectsHeader.length()) / 2;

        if (isLeft) {
            cout << setfill(' ') << setw(effectsHeaderPadding) << " " << effectsHeader << setw(71 - effectsHeaderPadding - effectsHeader.length()) << "|";
            cout << setw(70) << " " << endl;
        } else {
            cout << setw(70) << " " << "|";
            cout << setfill(' ') << setw(effectsHeaderPadding) << " " << effectsHeader << setw(69 - effectsHeaderPadding - effectsHeader.length()) << endl;
        }

        for (const auto& effect : character->getCurrentEffects()) {
            string effectString = effectToString(effect.first) + ": " + to_string(effect.second) + " turns";
            int effectPadding = (70 - effectString.length()) / 2;

            if (isLeft) {
                cout << setfill(' ') << setw(effectPadding) << " " << effectString << setw(71 - effectPadding - effectString.length()) << "|";
                cout << setw(70) << " " << endl;
            } else {
                cout << setw(70) << " " << "|";
                cout << setfill(' ') << setw(effectPadding) << " " << effectString << setw(69 - effectPadding - effectString.length()) << endl;
            }
        }
    }

    cout << setfill(' ') << setw(71) << "|" << endl;
}

void showBattleField(shared_ptr<Team> leftTeam, shared_ptr<Team> rightTeam) {
    cout << "=============================================================== Battle Field ===============================================================" << endl;

    string leftTeamName = toUpperCase(leftTeam->getName());
    string rightTeamName = toUpperCase(rightTeam->getName());

    int leftTeamPadding = (71 - leftTeamName.length()) / 2;
    int rightTeamPadding = (69 - rightTeamName.length()) / 2;

    cout << setfill(' ') << setw(leftTeamPadding) << " " << leftTeamName << setw(71 - leftTeamPadding - leftTeamName.length()) << "|";
    cout << setw(rightTeamPadding) << " " << rightTeamName << setw(69 - rightTeamPadding - rightTeamName.length()) << endl;

    cout << setfill(' ') << setw(71) << "|" << endl; 

    size_t maxSize = max(leftTeam->getMembers().size(), rightTeam->getMembers().size());
    for (size_t i = 0; i < maxSize; i++) {
        if (i < leftTeam->getMembers().size() && i < rightTeam->getMembers().size()) {

            string leftWeapons = leftTeam->getMembers()[i]->inventory().first ? leftTeam->getMembers()[i]->inventory().first->getName() : "";
            if (leftTeam->getMembers()[i]->inventory().second) {
                if (!leftWeapons.empty()) leftWeapons += " - ";
                leftWeapons += leftTeam->getMembers()[i]->inventory().second->getName();
            }

            string rightWeapons = rightTeam->getMembers()[i]->inventory().first ? rightTeam->getMembers()[i]->inventory().first->getName() : "";
            if (rightTeam->getMembers()[i]->inventory().second) {
                if (!rightWeapons.empty()) rightWeapons += " - ";
                rightWeapons += rightTeam->getMembers()[i]->inventory().second->getName();
            }

            showCharactersInfo(leftTeam->getMembers()[i], rightTeam->getMembers()[i]);
        } else if (i < leftTeam->getMembers().size()) {
            showSingleCharacterInfo(leftTeam->getMembers()[i], true);
        } else if (i < rightTeam->getMembers().size()) {
            showSingleCharacterInfo(rightTeam->getMembers()[i], false);
        }
    }

    cout << "============================================================================================================================================" << endl;
}