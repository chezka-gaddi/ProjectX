/**
 * @file
 * @brief
 * struct that contains the map and the dimensions of the field.
 */

#ifndef __MAP_DATA_H
#define __MAP_DATA_H
#include <vector>
#include <ostream>
#include <algorithm>

#include <map/Tile.h>
/*******************************************************************//**
 * @author David Donahue
 *
 * @struct MapData
 * @par Description:
 * The map ADT for the platform
 *
 *
 **********************************************************************/
class MapData
{
    public:
        int width;  /*!< The width value of the map */
        int height; /*!< The height value of the map */
        std::vector<std::vector<Tile>> tileMap;

        MapData(int w, int h);
        MapData(const MapData &m);
        MapData();
        ~MapData();

        void printTileMap();
        void clearTanks();
        void clearProjectiles();

    protected:
        void generateTileMap();
        void clearTileMap();
};

#endif