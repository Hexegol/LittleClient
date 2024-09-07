#include <windows.h>
#include <iostream>
#include "Cheat.h"

int main() {
    Cheat* cheat = new Cheat();
    char hotkey = 'F';

    while (true) {
        std::cout << "LittleClient, made by Hexegol" << std::endl;
        std::cout << "1. Change Speed" << std::endl;
        std::cout << "2. Change Hitbox" << std::endl;
        std::cout << "3. Change Reach" << std::endl;
        std::cout << "4. Self Destruct (return to default values before)" << std::endl;
        std::cout << "5. Reset All" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "7. Set hotkey for self-destruct (current = " << hotkey << ")" << std::endl;
        std::cout << "Enter your choice : ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            cheat->ChangeSpeed(false);
            break;
        case 2:
            cheat->ChangeHitbox(false);
            break;
        case 3:
            cheat->ChangeReach(false);
            break;
        case 4:
            cheat->ChangeSpeed(true);
            cheat->ChangeHitbox(true);
            cheat->ChangeReach(true);
            cheat->selfDestruct();
            cheat->emptyRecycleBin();

            break;
        case 5:
            cheat->ChangeSpeed(true);
            cheat->ChangeHitbox(true);
            cheat->ChangeReach(true);
            break;
        case 6:
            delete cheat;
            return 0;
        case 7:
            std::cout << "Enter new hotkey: ";
            char input;
            std::cin >> input;
            hotkey = toupper(input);
            std::cout << "Hotkey set to " << hotkey << std::endl;
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }

        if (GetAsyncKeyState(hotkey) & 0x8000) {
            cheat->selfDestruct();
            break;
        }

        Sleep(10);
    }

    delete cheat;
    return 0;
}
