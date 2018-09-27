/**
 * MapData.h
 * struct that contains the map and the dimensions of the field.
 */
#ifndef __MAP_DATA_H
#define __MAP_DATA_H
#include <vector>

struct MapData
{
    //row-major-order list the ID's of anything on the tiles on the map (tanks, projectiles, and obstacles)
    std::vector<int> map;
    int width, height;
};

#endif