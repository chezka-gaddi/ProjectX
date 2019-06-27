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
        /** row-major-order list the ID's of anything on the tiles on the map (tanks, projectiles, and obstacles) */
        std::vector<int> map;
        /*!< row-major-order map of obstacles, true means that an obstacle is present */
        std::vector<int> obstacleMap;
        std::vector<int> healthMap;
        int width;  /*!< The width value of the map */
        int height; /*!< The height value of the map */
        std::vector<std::vector<Tile>> tileMap;

        MapData(int w, int h);
        MapData(const MapData &m);
        MapData();
        ~MapData();
        void clear();
        void initMap();
        void printTileMap();
        void generateTileMap();
        void clearTileMap();
    private:
        void printMap(std::vector<int> tMap);
};
/* overload << to display to console */
std::ostream & operator<<(std::ostream& os, const MapData& md);
#endif
