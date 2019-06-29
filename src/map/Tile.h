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
    std::string type; //{Rock, Bush, Tree, Water, Crate, Tank, Projectile}
    int id;
    int x;
    int y;
    int health;
    Tile * actor = nullptr;
    Tile * projectile = nullptr;

    //constructor with initial values
    Tile(std::string t="empty", int newid=0, int newx=0, int newy=0, int h=0, Tile * nactor=nullptr, Tile * nproj=nullptr) 
        : type(t), id(newid), x(newx), y(newy), health(h), actor(nactor), projectile(nproj) {};
};
std::ostream & operator<<(std::ostream& os, const Tile& tile);
#endif