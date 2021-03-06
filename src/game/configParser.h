/***************************************************************************//**
* @file configParser.h
* @author Jonathan McKee
* @brief Contains new INI parser
*******************************************************************************/
#ifndef __parseconfig_h
#define __parseconfig_h

//#include <iostream>

#include <string>
#include <map/MapData.h>
#include <settings/Settings.h>

std::shared_ptr<MapData> parseConfig(const std::shared_ptr<Settings> & settings);
std::vector<std::string> parseList(const std::shared_ptr<Settings> & settings, std::string section, std::string key);
std::string parseAI(const std::shared_ptr<Settings> & settings, std::string section, std::string key);

#endif