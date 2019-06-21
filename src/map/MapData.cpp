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
    createMapArray(newMap, w, h);
    clearMap(w, h);
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
    this->map = m.map;
    this->obstacleMap = m.obstacleMap;
    this->healthMap = m.healthMap;

    initMap();

    for (int i = 0; i <= m.height; i++){
        for (int j = 0; j <= m.width; j++){
            this->newMap[i][j] = m.newMap[i][j];
        }
    }
}

/****************//*
 * @ author Jon McKee
 * @ par Description:
 * 
 * Deconstructor to clear our dynamic map
 ******************/
MapData::~MapData(){
    if (newMap != nullptr){
        deleteMapArray(newMap, height);
    }
}

/****************//*
 * @ author Jon McKee
 * @ par Description:
 * 
 * Function for initializing or emptying a map to nothing
 ******************/
void MapData::clearMap(int x, int y){
    for (int i = 0; i <= y; i++){
        for (int j = 0; j <= x; j++){
            newMap[i][j] = 0;
        }
    }
}

/****************//*
 * @ author Jon McKee
 * @ par Description:
 * 
 * Function for clearing 2d array
 ******************/
void MapData::clear(){
    //If we dont have a map, don't clear it
    if (newMap == nullptr)
        return;
    for (int i = 0; i <= height; i++){
        for (int j = 0; j <= width; j++){
            newMap[i][j] = 0;
        }
    }
}

/****************//*
 * @ author Jon McKee
 * @ par Description:
 * 
 * Function for initializing new map
 ******************/
void MapData::initMap(){
    createMapArray(newMap, width, height);
    clear();
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
void MapData::printNewMap(){
    for (int i = 1; i <= height; i++){
            for (int j=1; j <= width; j++){
                    std::cout << newMap[i][j] << " ";
                    if (j == width) 
                            std::cout << "\n";
            }
    }
    printf("Done.\n");
}

MapData::MapData() {}



/**************************************************************************//** 
 * @author Jonathan McKee
 * 
 * @par Description: 
 * This function allocates memory for our 2d map array using the number of columns
 * and rows passed into the function.  The pointer that is passed into the 
 * function is left pointing to the new array.  If an error occurs during the 
 * initial allocation the program will output an error message and error code 3.
 *
 * @param[in,out]   ptr - a pointer to our 2d array.
 * @param[in]   cols - The number of columns in our maze (X value).
 * @param[in]   rows - The number of rows in our maze (Y value).
 *
 * @returns 3 - Exits with code 3 if an error occurs allocating memory.
 *****************************************************************************/
void MapData::createMapArray( int ** &ptr, int cols, int rows )
{
    int i;
    cols++;rows++;
    ptr = new ( std::nothrow ) int *[rows+1];
    
    if ( ptr == nullptr )
    {
        printf("ERROR: Error allocating memory for game map.");
        exit ( 3 );
    }
    
    for ( i = 0; i <= rows; i++ )
    {
        ptr[i] = new ( std::nothrow ) int [cols+1];
        if ( ptr[i] == nullptr )
        {
            deleteMapArray( ptr, i );
            return;
        }
    }
}

/**************************************************************************//** 
 * @author Jonathan McKee
 * 
 * @par Description: 
 * This function deallocates memory from our 2d map array using the number of rows
 * passed into the function.  The function steps through the array passed into
 * the function and deletes the pointers in each spot of the initial array.
 *
 * @param[in,out]   arrptr - a pointer to our 2d array that will be deleted.
 * @param[in]   rows - The number of rows in our array that needs to be removed.
 *****************************************************************************/
void MapData::deleteMapArray( int **arrptr, int rows )
{
    int i;
    for ( i = 0; i <= rows; i++ ) 
    {
        delete [] arrptr[i];
    }
    delete [] arrptr;
}
