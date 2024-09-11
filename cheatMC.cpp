#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>
#include "Cheat.h"
#include "Config.h"

std::atomic<bool> stopThread(false);

void resetAll(Cheat* cheat, std::thread& noKnockbackThread) {
    stopThread = true;

    if (noKnockbackThread.joinable()) {
        noKnockbackThread.join();
    }

    cheat->ChangeSpeed(true);
    cheat->ChangeHitbox(true);
    cheat->ChangeReach(true);
    cheat->ChangeVelocity(true);
    cheat->EnableAirJump(true);
    cheat->EnableNoKnockback(true);

    stopThread = false;
}

void monitorNoKnockback(Cheat* cheat) {
    while (!stopThread) {
        cheat->EnableNoKnockback(false);
        Sleep(10);
    }
}

int main() {
    Cheat* cheat = new Cheat();
    std::thread noKnockbackThread;
    std::string fileName;

    if (!RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x46)) { // 0x46 est le code pour la touche 'F'
        std::cerr << "Failed to register hotkey" << std::endl;
        delete cheat;
        return 1;
    }

    std::cout << "Press F to trigger self-destruct" << std::endl;

    while (true) {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_HOTKEY && msg.wParam == 1) {
                cheat->selfDestruct();
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        std::cout << "LittleClient, made by Hexegol, please restart the program if bug occure" << std::endl;
        std::cout << "1. Change Speed" << std::endl;
        std::cout << "2. Change Hitbox" << std::endl;
        std::cout << "3. Change Reach" << std::endl;
        std::cout << "4. Enable Aimbot" << std::endl;
        std::cout << "5. Self Destruct (return to default values before)" << std::endl;
        std::cout << "6. Reset All" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "8. Set hotkey for self-destruct (current = F)" << std::endl;
        std::cout << "9. Enable air jump" << std::endl;
        std::cout << "10. Enable No Knockback (horizontal)" << std::endl;
        std::cout << "11. Change Velocity" << std::endl;
        std::cout << "12. save config" << std::endl;
        std::cout << "13. load config" << std::endl;
        std::cout << "Enter your choice : ";
        int choice;
        std::cin >> choice;

        switch (choice) 
        {
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
            cheat->EnableAimbot(false);
            break;
        case 5:
            resetAll(cheat, noKnockbackThread);
            cheat->selfDestruct();
            cheat->emptyRecycleBin();
            break;
        case 6:
            resetAll(cheat, noKnockbackThread);
            break;
        case 7:
            stopThread = true;
            if (noKnockbackThread.joinable()) {
                noKnockbackThread.join();
            }
            UnregisterHotKey(NULL, 1);
            delete cheat;
            return 0;
        case 8:
            std::cout << "Hotkey for self-destruct is already F" << std::endl;
            break;
        case 9:
            cheat->EnableAirJump(false);
            break;
        case 10:
            stopThread = true;
            if (noKnockbackThread.joinable()) {
                noKnockbackThread.join();
            }
            stopThread = false;
            noKnockbackThread = std::thread(monitorNoKnockback, cheat);
            break;
        case 11:
			cheat->ChangeVelocity(false);
			break;
        case 12:
            std::cout << "filename : ";
            std::cin >> fileName;
            {
                Config config(fileName.c_str());
                config.saveConfig((Cheat*)cheat);
            }
            break;
        default:
        {
            std::cout << "Invalid choice" << std::endl;
            break;
        }
        }

        Sleep(10);
    }

    stopThread = true;
    if (noKnockbackThread.joinable()) {
        noKnockbackThread.join();
    }

    UnregisterHotKey(NULL, 1);
    delete cheat;
    return 0;
}
