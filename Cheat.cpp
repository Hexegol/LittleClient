#include "Cheat.h"
#include <iostream>
#include <TlHelp32.h>
#include <windows.h>
#include <vector>
#include<tchar.h>
#include <list>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <chrono>
#include <thread>

DWORD Cheat::GetPID(const char* ProcessName) {
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(PROCESSENTRY32);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if (Process32First(processesSnapshot, &processInfo)) {
        do {
            if (!strcmp(processInfo.szExeFile, ProcessName)) {
                DWORD pid = processInfo.th32ProcessID;
                CloseHandle(processesSnapshot);
                return pid;
            }
        } while (Process32Next(processesSnapshot, &processInfo));
    }


    CloseHandle(processesSnapshot);
}

MODULEENTRY32 GetModule(const char* moduleName, unsigned long ProcessID)
{
    MODULEENTRY32 modEntry = { 0 };

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 curr = { 0 };

        curr.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &curr))
        {
            do
            {
                if (!strcmp(curr.szModule, moduleName))
                {
                    modEntry = curr;
                    break;
                }
            } while (Module32Next(hSnapshot, &curr));
        }
        CloseHandle(hSnapshot);
    }
    return modEntry;

}

uintptr_t Cheat::dwGetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
    uintptr_t dwModuleBaseAddress = 0;
    HANDLE hSnapshoot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
    MODULEENTRY32 ModuleEntry32 = { 0 };
    ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnapshoot, &ModuleEntry32))
    {
        do {
            if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
            {
                dwModuleBaseAddress = (uintptr_t)ModuleEntry32.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshoot, &ModuleEntry32));

    }
    CloseHandle(hSnapshoot);
    return dwModuleBaseAddress;
}



Cheat::Cheat()
{
    processName = L"Minecraft.Windows.exe";
}

Cheat::Cheat(std::wstring processName)
{
    this->processName = processName;
}

void Cheat::ChangeSpeed(bool resetvalues = false) {
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float mno = 20.0f;

    if(!resetvalues)
	{
        while (true)
        {
            std::cout << "Enter new speed between 20.0 and 200.0 ";
            std::cin >> mno;
            if (mno >= 20.0 && mno <= 200.0)
            {
                break;
            }
            else
            {
                std::cout << "Invalid speed" << std::endl;
            }
        }
	}
    else
    {
        mno = 20.0f;
    }

    uintptr_t timer = clientbase + 0x05AD91E8;
    //std::cout << pid << std::endl;
    //while (true)
    //{
        //std::cout << pid << std::endl;
        VirtualProtectEx(phandle, (LPVOID)(timer), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
        unsigned long long result;
        float timervalue = mno;

        // il faut mettre les offsets dans l'ordre inverse, comme avec la stack

        ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AD91E8), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x58), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x188), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x388), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x10), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x480), &result, sizeof(result), 0);
        WriteProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &timervalue, sizeof(timervalue), 0);
        Sleep(10);
    //}

}



void Cheat::ChangeHitbox(bool resetvalues = false) {
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float mno = 20.0f;

    if(!resetvalues)
	{
		while (true)
		{
			std::cout << "Enter new hitbox between 0.6 and 10.0 ";
			std::cin >> mno;
			if (mno >= 0.6 && mno <= 10.0)
			{
				break;
			}
			else
			{
				std::cout << "Invalid hitbox" << std::endl;
			}
		}
	}
	else
	{
		mno = 0.6f;
	}



    uintptr_t hitbox = clientbase + 0x05AF08B8;
    //std::cout << pid << std::endl;
    //while (true)
    //{
        //std::cout << pid << std::endl;
        VirtualProtectEx(phandle, (LPVOID)(hitbox), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
        unsigned long long result;
        float hitboxvalue = mno;
        // il faut mettre les offsets dans l'ordre inverse, comme avec la stack
        ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AF08B8), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x20), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0xC8), &result, sizeof(result), 0);
        ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x278), &result, sizeof(result), 0);
        WriteProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &hitboxvalue, sizeof(hitboxvalue), 0);
        Sleep(10);
    //}
}

void Cheat::ChangeReach(bool resetvalues = false)
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float mno = 3.0f;

    if (!resetvalues)
	{
        while (true)
        {
            std::cout << "Enter new reach between 3.0 and 7.0 ";
            std::cin >> mno;
            if (mno < 3.0 || mno > 7.0)
            {
                std::cout << "Invalid reach" << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }
	}
    else
    {
        mno = 3.0f;
    }

   
    
    uintptr_t reach = clientbase + 0x52880A8;
    //std::cout << pid << std::endl;
    //while (true)
    //{
        //std::cout << pid << std::endl;
        VirtualProtectEx(phandle, (LPVOID)(reach), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteProcessMemory(phandle, (LPCVOID*)reach, &mno, sizeof(mno), nullptr);
        Sleep(10);
    //}

}

bool Cheat::onHit()
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    uintptr_t velocityAddress = clientbase + 0x05AF08C8;
    float velocityValue;
    VirtualProtectEx(phandle, (LPVOID)velocityAddress, 256, PAGE_EXECUTE_READWRITE, &oldProtect);

    unsigned long long result;
    ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AF08C8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0xB8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x270), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &result, sizeof(result), 0);

    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &velocityValue, sizeof(velocityValue), 0);
    VirtualProtectEx(phandle, (LPVOID)velocityAddress, 256, oldProtect, &oldProtect);

    if(velocityValue > -0.03)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Cheat::ChangeVelocity(bool resetvalues)
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float velocity = 100.0f;
    //float horizontal = 100.0f;
    if (!resetvalues)
    {
        while (true)
        {
            std::cout << "enter value between 100 and 0 for velocity";
            std::cin >> velocity;
            if (velocity > 100 || velocity < 0)
            {
                std::cout << "Invalid" << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }
        /*
        while (true)
        {
            std::cout << "enter value between 100 and 0 for horizontal";
            std::cin >> horizontal;
            if (horizontal > 100 || horizontal < 0)
            {
                std::cout << "Invalid" << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }
        */
        
    }
    else
    {
        velocity = 100.0f;
        //horizontal = 100.0f;
    }
    
    while (true)
    {
        if(onHit())
		{
            uintptr_t velocityAddress = clientbase + 0x05AF08C8;
            float velocityValue;
            VirtualProtectEx(phandle, (LPVOID)velocityAddress, 256, PAGE_EXECUTE_READWRITE, &oldProtect);

            unsigned long long result;
            ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AF08C8), &result, sizeof(result), 0);
            ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &result, sizeof(result), 0);
            ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &result, sizeof(result), 0);
            ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0xB8), &result, sizeof(result), 0);
            ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x270), &result, sizeof(result), 0);
            ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &result, sizeof(result), 0);

            WriteProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &velocity, sizeof(velocity), 0);
		}
    }

}

void Cheat::EnableFly(bool resetvalues = false)
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float mno = 0.0f;


    std::cout << "work in progress";
    /*
    if (!resetvalues)
    {
        while (true)
        {
            std::cout << "0 to disable fly, 1 to enable fly";
            std::cin >> mno;
            if (mno < 0.0 || mno > 1.0)
            {
                std::cout << "Invalid" << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        mno = 0.0f;
    }
    */
    



    //uintptr_t fly = clientbase + 0x;

    //std::cout << pid << std::endl;
    //while (true)
    //{
        //std::cout << pid << std::endl;
    //VirtualProtectEx(phandle, (LPVOID)(fly), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
    //WriteProcessMemory(phandle, (LPCVOID*)fly, &mno, sizeof(mno), nullptr);
    //Sleep(10);
    //}
}

namespace Aimbot
{
#include "Cheat.h"
    struct Vector3
    {
        float x, y, z;
    };

    struct Player {
        Vector3 position;
        Vector3 viewDirection;
    };

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

    void CalculateAngles(const Vector3& from, const Vector3& to, float& yaw, float& pitch) {
        Vector3 delta = { to.x - from.x, to.y - from.y, to.z - from.z };

        yaw = atan2(delta.z, delta.x) * (180.0f / M_PI);
        pitch = atan2(delta.y, sqrt(delta.x * delta.x + delta.z * delta.z)) * (180.0f / M_PI);
    }

    uintptr_t FindPattern(HANDLE process, const char* pattern, const char* mask, uintptr_t baseAddress, size_t size)
    {
        std::vector<unsigned char> buffer(size);
        SIZE_T bytesRead;
        if (ReadProcessMemory(process, (LPCVOID)baseAddress, buffer.data(), size, &bytesRead))
        {
            for (size_t i = 0; i < bytesRead - strlen(mask); i++)
            {
                bool found = true;
                for (size_t j = 0; j < strlen(mask); j++)
                {
                    if (mask[j] == 'x' && buffer[i + j] != pattern[j])
                    {
                        found = false;
                        break;
                    }
                    else if (mask[j] == '?' && buffer[i + j] == pattern[j])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return baseAddress + i;
                }
            }
        }
        return 0;
    }
}



void Cheat::EnableAimbot(bool resetvalues)
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (phandle == NULL) {
        std::cerr << "Failed to open process" << std::endl;
        return;
    }

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    std::cout << "work in progress" << std::endl;

    uintptr_t xBaseAddress = clientbase + 0x05AF08B8;
    uintptr_t yBaseAddress = clientbase + 0x05AF08B8;
    uintptr_t zBaseAddress = clientbase + 0x05AF08C8;
    float xResult;
    uintptr_t xCurrentAddress = xBaseAddress;
    if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
        xCurrentAddress += 0x0;
        if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
            xCurrentAddress += 0x18;
            if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
                xCurrentAddress += 0x90;
                if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
                    xCurrentAddress += 0x98;
                    if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
                        xCurrentAddress += 0xB8;
                        if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
                            xCurrentAddress += 0x270;
                            if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xCurrentAddress, sizeof(xCurrentAddress), nullptr)) {
                                xCurrentAddress += 0x0;
                                if (ReadProcessMemory(phandle, (LPCVOID)xCurrentAddress, &xResult, sizeof(xResult), nullptr)) {
                                    std::cout << "X Result: " << xResult << std::endl;
                                }
                                else {
                                    std::cerr << "Failed to read final memory address for X position" << std::endl;
                                }
                            }
                            else {
                                std::cerr << "Failed to read memory at offset +0x270" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "Failed to read memory at offset +0xB8" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "Failed to read memory at offset +0x98" << std::endl;
                    }
                }
                else {
                    std::cerr << "Failed to read memory at offset +0x90" << std::endl;
                }
            }
            else {
                std::cerr << "Failed to read memory at offset +0x18" << std::endl;
            }
        }
        else {
            std::cerr << "Failed to read memory at initial address for X position" << std::endl;
        }
    }
    else {
        std::cerr << "Failed to read initial memory address for X position" << std::endl;
    }
    float yResult;
    uintptr_t yCurrentAddress = yBaseAddress;
    if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
        yCurrentAddress += 0x0;
        if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
            yCurrentAddress += 0x0;
            if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                yCurrentAddress += 0x8;
                if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                    yCurrentAddress += 0x18;
                    if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                        yCurrentAddress += 0xB8;
                        if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                            yCurrentAddress += 0x278;
                            if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                                yCurrentAddress += 0x4;
                                if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yResult, sizeof(yResult), nullptr)) {
                                    std::cout << "Y Result: " << yResult << std::endl;
                                }
                                else {
                                    std::cerr << "Failed to read final memory address for Y position" << std::endl;
                                }
                            }
                            else {
                                std::cerr << "Failed to read memory at offset +0x278" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "Failed to read memory at offset +0xB8" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "Failed to read memory at offset +0x18" << std::endl;
                    }
                }
                else {
                    std::cerr << "Failed to read memory at offset +0x8" << std::endl;
                }
            }
            else {
                std::cerr << "Failed to read memory at offset +0x0" << std::endl;
            }
        }
        else {
            std::cerr << "Failed to read memory at offset +0x0" << std::endl;
        }
    }
    else {
        std::cerr << "Failed to read initial memory address" << std::endl;
    }

    float zResult;
    uintptr_t zCurrentAddress = zBaseAddress;
    if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
        zCurrentAddress += 0x0;
        if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
            zCurrentAddress += 0x0;
            if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
                zCurrentAddress += 0x20;
                if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
                    zCurrentAddress += 0xA0;
                    if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
                        zCurrentAddress += 0xB8;
                        if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
                            zCurrentAddress += 0x270;
                            if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zCurrentAddress, sizeof(zCurrentAddress), nullptr)) {
                                zCurrentAddress += 0x8;
                                if (ReadProcessMemory(phandle, (LPCVOID)zCurrentAddress, &zResult, sizeof(zResult), nullptr)) {
                                    std::cout << "Z Result: " << zResult << std::endl;
                                }
                                else {
                                    std::cerr << "Failed to read final memory address for Z position" << std::endl;
                                }
                            }
                            else {
                                std::cerr << "Failed to read memory at offset +0x270" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "Failed to read memory at offset +0xB8" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "Failed to read memory at offset +0xA0" << std::endl;
                    }
                }
                else {
                    std::cerr << "Failed to read memory at offset +0x20" << std::endl;
                }
            }
            else {
                std::cerr << "Failed to read memory at offset +0x0" << std::endl;
            }
        }
        else {
            std::cerr << "Failed to read memory at initial address for Z position" << std::endl;
        }
    }
    else {
        std::cerr << "Failed to read initial memory address for Z position" << std::endl;
    }


    //view direction
    
    Aimbot::Player player = { {xResult, yResult, zResult}, {0.0f, 0.0f, 1.0f} };
    
    Aimbot::Vector3 target = { 10.0f, 5.0f, 10.0f };

    float yaw, pitch;
    unsigned char aob[] = { 0x3E, 0x57, 0x7B, 0xBF, 0x99, 0x56, 0x7B, 0xBF };
    // inverser yaw et pitch si il faut
    std::memcpy(&pitch, aob, sizeof(float));

    std::memcpy(&yaw, aob + sizeof(float), sizeof(float));



    Aimbot::CalculateAngles(player.position, target, yaw, pitch);

    

    uintptr_t yawAddress = clientbase + 0x05A62958;
    uintptr_t pitchAddress = clientbase + 0x05A62958;

    VirtualProtectEx(phandle, (LPVOID)yawAddress, sizeof(yaw), PAGE_EXECUTE_READWRITE, &oldProtect);
    VirtualProtectEx(phandle, (LPVOID)pitchAddress, sizeof(pitch), PAGE_EXECUTE_READWRITE, &oldProtect);

    ReadProcessMemory(phandle, (void*)yawAddress, &yaw, sizeof(yaw), 0);
    ReadProcessMemory(phandle, (void*)pitchAddress, &pitch, sizeof(pitch), 0);

    std::cout << "Yaw: " << yaw << ", Pitch: " << pitch << std::endl;
    CloseHandle(phandle);
}

void Cheat::EnableAirJump(bool resetvalues)
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float mno = 0.0f;

    if (!resetvalues)
    {
        while (true)
        {
            std::cout << "Enter  ";
            std::cin >> mno;
            if (mno > 0.0 && mno < 1.0)
            {
                break;
            }
            else
            {
                std::cout << "Invalid" << std::endl;
            }
        }
    }
    else
    {
        mno = 0.0f;
    }

    std::cout << "work in progress" << std::endl;

    /*
    uintptr_t airJump = clientbase + 0x05AF08B8;
    //while (true)
    //{
    VirtualProtectEx(phandle, (LPVOID)(airJump), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
    unsigned long long result;
    float airJumpValue = mno;

    ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AF08B8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x20), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0xC8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x278), &result, sizeof(result), 0);
    WriteProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &airJumpValue, sizeof(airJumpValue), 0);
    Sleep(10);
    //}
    */
    
}

#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

void Cheat::EnableNoKnockback(bool resetvalues)
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float mno = 0.0f;
    float yInitialPosition = 0.0f;

    if (!resetvalues)
    {
        while (true)
        {
            std::cout << "Enter multiplier (0.0 or 1.0): ";
            std::cin >> mno;
            if (mno == 0.0 || mno == 1.0)
            {
                break;
            }
            else
            {
                std::cout << "Invalid value. Please enter 0.0 or 1.0." << std::endl;
            }
        }
    }
    else
    {
        mno = 0.0f;
    }

    std::cout << "horizontal knockback enabled, Monitoring player Y position" << std::endl;
    if(resetvalues == true)
	{
		std::cout << "horizontal Knockback disabled" << std::endl;
	}
	else
	{
        while (true)
        {
            unsigned long long result;
            uintptr_t yBaseAddress = clientbase + 0x05AF08B8;
            VirtualProtectEx(phandle, (LPVOID)(yBaseAddress), 256, PAGE_EXECUTE_READWRITE, &oldProtect);
            float yCurrentPosition = 0.0f;

            uintptr_t yCurrentAddress = yBaseAddress;

            if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                yCurrentAddress += 0x0;
                if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                    yCurrentAddress += 0x18;
                    if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                        yCurrentAddress += 0xB8;
                        if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                            yCurrentAddress += 0x278;
                            if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentAddress, sizeof(yCurrentAddress), nullptr)) {
                                yCurrentAddress += 0x4;
                                if (ReadProcessMemory(phandle, (LPCVOID)yCurrentAddress, &yCurrentPosition, sizeof(yCurrentPosition), nullptr)) {
                                    if (yInitialPosition == 0.0f) {
                                        yInitialPosition = yCurrentPosition;
                                    }
                                    if (yCurrentPosition != yInitialPosition) {
                                        WriteProcessMemory(phandle, (void*)(yCurrentAddress), &yInitialPosition, sizeof(yInitialPosition), nullptr);
                                    }
                                }
                                else {
                                    std::cerr << "Failed to read final memory address for Y position" << std::endl;
                                }
                            }
                            else {
                                std::cerr << "Failed to read memory at offset +0x278" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "Failed to read memory at offset +0xB8" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "Failed to read memory at offset +0x18" << std::endl;
                    }
                }
                else {
                    std::cerr << "Failed to read memory at offset +0x8" << std::endl;
                }
            }
            else {
                std::cerr << "Failed to read initial memory address" << std::endl;
            }
            Sleep(10);
        }
	}
    
}


void Cheat::emptyRecycleBin() {
    HRESULT result = SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);

    if (result == S_OK) {
        std::cout << "recycle bin emptied successfully" << std::endl;
    }
    else {
        std::cerr << "failed to empty the recycle bin" << std::endl;
    }
}

float Cheat::getSpeed() {
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float timerValue = 0.0f;
    DWORD oldProtect = 0;
    uintptr_t timerAddress = clientbase + 0x05AD91E8;
    VirtualProtectEx(phandle, (LPVOID)timerAddress, 256, PAGE_EXECUTE_READWRITE, &oldProtect);

    unsigned long long result;
    ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AD91E8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x58), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x188), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x388), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x10), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x480), &result, sizeof(result), 0);

    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &timerValue, sizeof(timerValue), 0);
    VirtualProtectEx(phandle, (LPVOID)timerAddress, 256, oldProtect, &oldProtect);

    CloseHandle(phandle);

    return timerValue;
}


float Cheat::getHitbox() {
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float hitboxValue = 0.0f;
    uintptr_t hitboxAddress = clientbase + 0x05AF08B8;
    VirtualProtectEx(phandle, (LPVOID)hitboxAddress, 256, PAGE_EXECUTE_READWRITE, &oldProtect);

    unsigned long long result;
    ReadProcessMemory(phandle, (void*)((unsigned long long)clientbase + 0x05AF08B8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x0), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x20), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0xC8), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x278), &result, sizeof(result), 0);
    ReadProcessMemory(phandle, (void*)((unsigned long long)result + 0x18), &hitboxValue, sizeof(hitboxValue), 0);
    VirtualProtectEx(phandle, (LPVOID)hitboxAddress, 256, oldProtect, &oldProtect);

    CloseHandle(phandle);

    return hitboxValue;
}


float Cheat::getReach() {
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);

    float reachValue = 0.0f;
    uintptr_t reachAddress = clientbase + 0x52880A8;

    VirtualProtectEx(phandle, (LPVOID)reachAddress, 256, PAGE_EXECUTE_READWRITE, &oldProtect);
    ReadProcessMemory(phandle, (LPCVOID)reachAddress, &reachValue, sizeof(reachValue), nullptr);
    VirtualProtectEx(phandle, (LPVOID)reachAddress, 256, oldProtect, &oldProtect);

    CloseHandle(phandle);

    return reachValue;
}


float Cheat::getVerticalVelocity()
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);
}

float Cheat::getHorizontalVelocity()
{
    unsigned long long pid = GetPID("Minecraft.Windows.exe");
    MODULEENTRY32 module = GetModule("Minecraft.Windows.exe", pid);
    HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    char moduleName[] = "Minecraft.Windows.exe";
    DWORD oldProtect = 0;
    uintptr_t clientbase = dwGetModuleBaseAddress((moduleName), pid);
}

void Cheat::selfDestruct()
{
    char executablePath[MAX_PATH];
    GetModuleFileName(NULL, executablePath, MAX_PATH);
    std::string batchFilePath = std::string(executablePath) + ".bat";
    std::ofstream script(batchFilePath.c_str());

    if (script.is_open()) {
        script << "@echo off\n"
            << "timeout /T 2 /NOBREAK\n" 
            << "del \"" << executablePath << "\"\n"  
            << "if exist \"" << executablePath << "\" goto Repeat\n"
            << "del \"" << batchFilePath << "\"\n" 
            << ":Repeat\n"
            << "goto Repeat\n";  
        script.close();
        std::cout << "creating the batch file for self destruction : " << batchFilePath << std::endl;
        system(("start " + batchFilePath).c_str());
        exit(0);
    }
    else {
        std::cerr << "impossible to create the batch file" << std::endl;
    }
}
