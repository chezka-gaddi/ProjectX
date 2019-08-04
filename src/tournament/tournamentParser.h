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
#include <structures/attributes.h>

std::vector<bracket> parseBrackets();
attributes parseStats(std::string);
std::vector<std::pair<int,int>> parseSpawns(std::string);
void parseSettings(std::string, std::shared_ptr<Settings>);
std::vector<player> parsePlayers();
void parseImages();

#endif