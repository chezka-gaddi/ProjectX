/** @file 
 @brief overloaded output function for the mapdata structure.  Only outputs the game obstacle map.
 */

#include "MapData.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const MapData& md)
{
    int i, j;
    //ANSI Stuff
    os << "\x1B[2J"; // clear screen and home cursor
    os << " ";
    for	(j = 0; j < md.width; ++j)
    {
        if ( j < 10 )
            os << "   " << j << "   ";
        else
            os << "   " << j << "  ";
    }
    os << '\n';
    os << ' ';
    for (j = 0; j < md.width; ++j)
    {
        os << " ______";
    }
    os << '\n';
    for (i = 0; i < md.height; ++i)
    {
        os << " |";
        for (j = 0; j < md.width; ++j) //top of cell
        {
            os << "      |";
        }
        os <<"\n |";
        for (j = 0; j < md.width; ++j) // top of the 'sprite'
        {
            if (md.map[j+i*md.width] > 0) //tank actor
            {
                os << "  o-o |";
            }
            else if (md.obstacleMap[j + i*md.width]) //Obstacle
            {
                os << "******|";
            }
            else
            {
                os << "      |";
            }
        }
        os <<"\n" << i <<"|";
        for (j = 0; j < md.width; ++j) //middle of cell
        {
            if (md.map[j+i*md.width] > 0) //tank actor
            {
                os << "  |" << md.map[j+i*md.width] << "| |";
            }
            else if (md.map[j+i*md.width] < 0) // projectile actor
            {
                os << "   *  |";
            }
            else if (md.obstacleMap[j + i*md.width]) //Obstacle
            {
                os << "******|";
            }
            else
            {
                os << "      |";
            }
        }
        os <<"\n" << " |";
        for (j = 0; j < md.width; ++j) //bottom of 'sprite'
        {
            if (md.map[j+i*md.width] > 0) //tank actor
            {
                os << "  o-o |";
            }
            else if (md.obstacleMap[j + i*md.width]) //Obstacle
            {
                os << "******|";
            }
            else
            {
                os << "      |";
            }
        }
        os <<"\n |";
        for (j = 0; j < md.width; ++j) //bottom of cell
        {
            os << "______|";
        }
        os << '\n'; //end of row
    }

    return os;
}

/*****************//*
 * Author Original Developers
 * Constructor for the MapData object.  Resizes and creates a proper size obstacleMap
 *
 *******************/
MapData::MapData(int w, int h) : width(w), height(h)
{
    map.resize(w * h);
    obstacleMap.resize(w * h);
    std::fill(map.begin(), map.end(), 0);
    std::fill(obstacleMap.begin(), obstacleMap.end(), false);
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
            tileMap[i][j] = Tile("Empty", 0, j, i, 0, nullptr); //default empty tiles
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
            tileMap[i][j] = Tile("Empty", 0, j, i, 0, nullptr); //default empty tiles
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
    //this->map = m.map;
    this->obstacleMap = m.obstacleMap;
    this->healthMap = m.healthMap;
    this->tileMap = m.tileMap;
}

/****************//*
 * @ author Jon McKee
 * @ par Description:
 * 
 * Deconstructor to clear our dynamic map
 ******************/
MapData::~MapData(){
}

/****************//*
 * @ author Jon McKee
 * @ brief a printMap function to any specified map array as a 2d ascii map
 ******************/
void MapData::printMap(std::vector<int> tMap){
    for (int i = 0; i < height; i++){
            for (int j=0; j < width;j++){
                    std::cout << tMap[j+i*width] << " ";
                    if (j == width-1) 
                            std::cout << "\n";
            }
    }
}

/****************//*
 * @ author Jon McKee
 * @ brief a printMap function to any specified map array as a 2d ascii map
 ******************/
void MapData::printTileMap(){
    for (int i = 1; i <= height; i++){
            for (int j=1; j <= width; j++){
                    std::cout << tileMap[i][j] << "  ";
                    if (j == width) 
                        std::cout << "\n";
            }
    }
    printf("Done.\n");
}

MapData::MapData() {}