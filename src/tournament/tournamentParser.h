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
#include "player.h"

std::vector<bracket> parseBrackets();
void parseStats();
std::vector<std::pair<int,int>> parseSpawns(std::string);
void parseSettings();
std::vector<player> parsePlayers();
void parseImages();

#endif