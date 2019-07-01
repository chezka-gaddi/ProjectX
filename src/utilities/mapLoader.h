#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <map/MapData.h>
#include <settings/Settings.h>

#ifndef __MAPLOADER_H__
#define __MAPLOADER_H__
std::shared_ptr<MapData> loadMap(std::shared_ptr<Settings> settings);


#endif