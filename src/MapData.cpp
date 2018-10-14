/** @file */

#include "MapData.h"

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

MapData::MapData(int w, int h) : width(w), height(h)
{
    map.resize(w * h);
    obstacleMap.resize(w * h);
    std::fill(map.begin(), map.end(), 0);
    std::fill(obstacleMap.begin(), obstacleMap.end(), false);
}
MapData::MapData() {}
