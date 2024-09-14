#include "Config.h"
#include <string.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream> 

bool Config::isJsonFile()
{
    for (int i = 0; i < strlen(filename_); i++)
    {
        if (filename_[i] == '.')
        {
            if (filename_[i + 1] == 'j' && filename_[i + 2] == 's' && filename_[i + 3] == 'o' && filename_[i + 4] == 'n')
            {
                return true;
            }
            else return false;
        }
    }
    return false; 
}

Config::Config(const char* filename)
{
    filename_ = filename;
}

Config::~Config() {}

void Config::saveConfig(Cheat* cheat)
{
    auto configJson = nlohmann::json::object();
    configJson["speed"] = cheat->getSpeed();
    configJson["hitbox"] = cheat->getHitbox();
    configJson["reach"] = cheat->getReach();
    //configJson["velocity"]["vertical"] = cheat.getVerticalVelocity();
    //configJson["velocity"]["horizontal"] = cheat.getHorizontalVelocity();

    if (isJsonFile())
    {
        std::ofstream file(filename_);
        if (file.is_open()) {
            file << configJson.dump(4);
            file.close();
        }
        else {
            std::cerr << "Cannot save the config file" << std::endl;
        }
    }
    else
    {
        std::cout << "The config file must be a JSON file\n";
    }
}

void Config::loadConfig()
{
}

void Config::printConfig()
{
}
