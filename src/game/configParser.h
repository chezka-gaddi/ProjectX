/***************************************************************************//**
* @file configParser.h
* @author Jonathan McKee
* @brief Contains new INI parser
*******************************************************************************/
#ifndef __parseconfig_h
#define __parseconfig_h

#include <utilities/inireader.h>
#include <utilities/mapLoader.h>
#include <map/MapData.h>
#include <string>
#include <iostream>

#include <settings/Settings.h>

MapData * parseConfig(Settings *);

#endif