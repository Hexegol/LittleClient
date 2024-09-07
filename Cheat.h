#pragma once
#include <string>
#include <windows.h>

class Cheat
{
private:
	float speed;
	std::wstring processName;
	DWORD GetPID(const char* ProcessName);
	//MODULEENTRY32 GetModule(const char* moduleName, unsigned long ProcessID);
	uintptr_t dwGetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID);
public:
	Cheat();
	Cheat(std::wstring processName);

	void ChangeSpeed(bool resetvalues);
	void ChangeHitbox(bool resetvalues);
	void ChangeReach(bool resetvalues);
	void EnableFly(bool resetvalues);
	void selfDestruct();
	void emptyRecycleBin();
};

