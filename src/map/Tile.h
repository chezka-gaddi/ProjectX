/**
 * @file
 * @brief
 * struct that contains the format for obstacles
 */

#ifndef __Tile_H__
#define __Tile_H__
#include <string>
#include <ostream>

struct Tile{
    std::string type; //{Rock, Bush, Tree, Water, Tank, Projectile}
    int x;
    int y;
    int health;
    Tile * actor = nullptr;

    //constructor with initial values
    Tile(std::string t="empty", int newx=0, int newy=0, int h=0, Tile * nactor=nullptr) 
        : type(t), x(newx), y(newy), health(h), actor(nactor) {};
};
std::ostream & operator<<(std::ostream& os, const Tile& tile);
#endif