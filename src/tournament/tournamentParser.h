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

std::vector<bracket> parseBracket();
void parseStats();
void parseSpawns();
void parseSettings();
void parsePlayers();
void parseImages();

#endif