#include "../headers/team_creation.hpp"
#include "../../../Ej2/characters/character.hpp"
#include "../../../Ej3/headers/factory.hpp"
#include "../../../Ej3/headers/funcs.hpp"
#include "../../../Ej3/headers/team.hpp"

void displayTeamSlots(const shared_ptr<Team> team) {
    vector<shared_ptr<Character>> members = team->getMembers();

    cout << " __            __    __            __    __            __    __            __    __            __ " << endl;
    cout << "|                |  |                |  |                |  |                |  |                |" << endl;
    cout << "|                |  |                |  |                |  |                |  |                |" << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "|";
        if (i < static_cast<int>(members.size()) && members[i]) {
            string name = members[i]->getName();
            int padding = (16 - name.length()) / 2; // Calculate padding for centering
            cout << setw(padding + name.length()) << name << setw(16 - padding - name.length()) << " ";
        } else {
            cout << "     SLOT " << (i + 1) << "     ";
        }
        cout << "|  ";
    }
    cout << endl;

    for (int i = 0; i < 5; ++i) {
        cout << "|";
        if (i < static_cast<int>(members.size()) && members[i]) {
            string type = "(" + members[i]->getType() + ")";
            int padding = (16 - type.length()) / 2; // Calculate padding for centering
            cout << setw(padding + type.length()) << type << setw(16 - padding - type.length()) << " ";
        } else {
            string empty = "(Empty).";
            int padding = (16 - empty.length()) / 2; // Calculate padding for centering
            cout << setw(padding + empty.length()) << empty << setw(16 - padding - empty.length()) << " ";
        }
        cout << "|  ";
    }
    cout << endl;

    cout << "|                |  |                |  |                |  |                |  |                |" << endl;
    cout << "|__            __|  |__            __|  |__            __|  |__            __|  |__            __|" << endl;
}

void teamCreation(shared_ptr<Team> team) {
    while (true) {
        // Clear the screen
        clearScreen();

        // Display the team creation header
        string teamName = team->getName();
        string header = "=============================================================== " + team->getName() + " Creation ===============================================================";
        int padding = (140 - header.length()) / 2;
        cout << setfill(' ') << setw(padding) << " " << header << setw(140 - padding - header.length()) << endl;

        // Display the current team slots
        displayTeamSlots(team);

        // Display combined options for warriors and mages
        cout << "\nChoose a character to add to your team:" << endl;
        cout << "1. Barbarian" << endl;
        cout << "2. Gladiator" << endl;
        cout << "3. Knight" << endl;
        cout << "4. Mercenary" << endl;
        cout << "5. Paladin" << endl;
        cout << "6. Conjurer" << endl;
        cout << "7. Necromancer" << endl;
        cout << "8. Sorcerer" << endl;
        cout << "9. Warlock" << endl;
        cout << "10. Delete a character" << endl;
        cout << "0. Finish team creation" << endl;

        // Get user input
        int input;
        cout << "Enter your choice: ";
        cin >> input;

        if (input == 0) {
            break; // Exit the loop
        }

        if (input == 10) {
            // Delete a character
            int slot;
            cout << "Enter the slot number (1-5) of the character to delete: ";
            cin >> slot;

            if (slot < 1 || slot > 5 || slot > static_cast<int>(team->getMembers().size())) {
                cout << "Invalid slot. Please try again." << endl;
                system("PAUSE"); // Pause to let the user read the message
                continue;
            }

            team->loseMember(team->getMembers()[slot - 1]); // Adjust for 0-based indexing
            cout << "Character in slot " << slot << " has been removed." << endl;
            system("PAUSE"); // Pause to let the user read the message
            continue;
        }

        // Determine the character type to add
        shared_ptr<Character> newCharacter = nullptr;
        if (input >= 1 && input <= 9) {
            newCharacter = Factory::createCharacter(static_cast<CharacterType>(input - 1), getRandomName(static_cast<CharacterType>(input - 1)));
        } else {
            cout << "Invalid choice. Please try again." << endl;
            system("PAUSE"); // Pause to let the user read the message
            continue;
        }

        // If the team is full, ask for a slot to replace
        if (team->getMembers().size() >= 5) {
            int slot;
            cout << "Choose a slot to delete (1-5): ";
            cin >> slot;

            if (slot < 1 || slot > 5) {
                cout << "Invalid slot. Please try again." << endl;
                system("PAUSE"); // Pause to let the user read the message
                continue;
            }

            // Replace the member in the chosen slot
            team->loseMember(team->getMembers()[slot - 1]); // Adjust for 0-based indexing
        }

        // Add the new character to the team using Factory
        Factory::addCharacterToTeam(team, newCharacter);
        team->sortMembersByType();
    }
}