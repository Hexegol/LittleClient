#include "Cheat.h"
#include <iostream>
#include <TlHelp32.h>
#include <windows.h>
#include <vector>
#include<tchar.h>
#include <list>
#include <fstream>

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

void Cheat::emptyRecycleBin() {
    HRESULT result = SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);

    if (result == S_OK) {
        std::cout << "recycle bin emptied successfully" << std::endl;
    }
    else {
        std::cerr << "failed to empty the recycle bin" << std::endl;
    }
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
