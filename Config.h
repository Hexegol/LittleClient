#pragma once
#include "Cheat.h"
class Config
{
private:
	const char* filename_;
	bool isJsonFile();
public:
	Config(const char* filename);
	~Config();
	void saveConfig(Cheat* cheat);
	void loadConfig();
	void printConfig();
};

