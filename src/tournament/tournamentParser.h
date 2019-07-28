/***************************************************************************//**
* @file configParser.h
* @author Jonathan McKee
* @brief Contains new INI parser
*******************************************************************************/
#ifndef __tournamentParser_h
#define __tournamentParser_h

#include <string>
#include <map/MapData.h>
#include <settings/Settings.h>
#include "bracket.h"

std::vector<bracket> parseBrackets();
void parseStats();
void parseSettings();
std::vector<player> parsePlayers();
void parseImages();

#endif