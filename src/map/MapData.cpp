/** @file 
 @brief overloaded output function for the mapdata structure.  Only outputs the game obstacle map.
 */

#include "MapData.h"
#include <iostream>
#include <ostream>
#include <algorithm>

/*****************//*
 * Author Original Developers
 * Constructor for the MapData object.  Resizes and creates a proper size obstacleMap
 *
 *******************/
MapData::MapData(int w, int h) : width(w), height(h)
{
    generateTileMap();
}

/*****************//*
 * Author: Jon McKee
 * 
 * This function resizes the tile map and then fills it with empty tiles.
 *******************/
void MapData::generateTileMap()
{
    int h = height + 1; //Add 1 so we can use 1 based coordinate system
    int w = width + 1;
    if (h == 0 || w == 0){ //If either value is 0 we don't need a map
        clearTileMap(); //Clear any old data
        return;
    }
    tileMap.resize(h); 
    for(int i = 0; i < (int) tileMap.size(); i++){
        tileMap[i].resize(w);
        for (int j = 0; j < (int) tileMap[i].size(); j++){
            tileMap[i][j] = Tile("Empty", 0, j, i, 0, direction::STAY); //default empty tiles
        }
    }
}

/*****************//*
 * Author: Jon McKee
 * 
 * This function clears the tileMap
 *******************/
void MapData::clearTileMap()
{
    for(int i = 0; i < (int) tileMap.size(); i++){
        for (int j = 0; j < (int) tileMap[i].size(); j++){
            tileMap[i][j].type = "Empty";
            tileMap[i][j].id = 0;
            tileMap[i][j].x = j;
            tileMap[i][j].y = i;
            tileMap[i][j].health = 0;

            tileMap[i][j].tank = nullptr;
            tileMap[i][j].projectile = nullptr;

        }
    }
}

/*****************//*
 * @Author Jon McKee
 * @par Description:
 * Copy constructor for the MapData object.  Allows copying 
 * the MapData object
 *******************/
MapData::MapData(const MapData &m)
{
    this->width = m.width;
    this->height = m.height;
    this->tileMap = m.tileMap;
}

/****************//*
 * @ author Jon McKee
 * @ par Description:
 * 
 * Deconstructor to clear our dynamic map
 ******************/
MapData::~MapData(){
    for(int i = 0; i < (int) tileMap.size(); i++){
        tileMap[i].clear();
    }
    tileMap.clear();
}

/****************//*
 * @ author Jon McKee
 * @ brief a printMap function to any specified map array as a 2d ascii map
 ******************/
void MapData::printTileMap(){
    for (int i = 1; i <= height; i++){
            for (int j=1; j <= width; j++){
                    std::cout << tileMap[i][j] << "  "; //Left as cout because of the operator overload
                    if (j == width) 
                        printf("\n");
            }
    }
    printf("Done.\n");
}

MapData::MapData() {}

/*****************//*
 * Author: Jon McKee
 * 
 * This function clears all tanks from the tileMap
 *******************/
void MapData::clearTanks()
{
    for(int i = 0; i < (int) tileMap.size(); i++){
        for (int j = 0; j < (int) tileMap[i].size(); j++){
            if (tileMap[i][j].tank != nullptr){
                //delete tileMap[i][j].tank;
                tileMap[i][j].tank = nullptr;
            }
        }
    }
}

/*****************//*
 * Author: Jon McKee
 * 
 * This function clears all projectiles from the tileMap
 *******************/
void MapData::clearProjectiles()
{
    for(int i = 0; i < (int) tileMap.size(); i++){
        for (int j = 0; j < (int) tileMap[i].size(); j++){
            if (tileMap[i][j].projectile != nullptr){
                //delete tileMap[i][j].projectile;
                tileMap[i][j].projectile = nullptr;
            }
        }
    }
}