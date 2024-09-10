#pragma once
#include <string>
#include <windows.h>

class Cheat
{
private:
	std::wstring processName;
	//MODULEENTRY32 GetModule(const char* moduleName, unsigned long ProcessID);
	DWORD GetPID(const char* ProcessName);
	uintptr_t dwGetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID);
public:
	Cheat();
	Cheat(std::wstring processName);
	
	void ChangeSpeed(bool resetvalues);
	void ChangeHitbox(bool resetvalues);
	void ChangeReach(bool resetvalues);
	void EnableFly(bool resetvalues);
	void EnableAimbot(bool resetvalues);
	void EnableAirJump(bool resetvalues);
	void EnableNoKnockback(bool resetvalues);
	void selfDestruct();
	void emptyRecycleBin();
};

