/**
 * @file
 * @brief
 * struct that contains the format for obstacles
 */

#ifndef __Tile_H__
#define __Tile_H__
#include <string>
#include <ostream>
#include <memory>
#include <structures/direction.h>


struct Tile{
    std::string type="Empty"; //{Rock, Bush, Tree, Water, Crate, Hedgehog}
    int id = 0;
    int x = 0;
    int y = 0;
    int health = 0;
    direction dir = direction::UP;
    std::shared_ptr<Tile> tank; //Tanks go here
    std::shared_ptr<Tile> projectile; //Projectiles go here
    //constructor with initial values
    Tile(std::string t="Empty", int newid=0, int newx=0, int newy=0, int h=0, direction d=direction::UP) 
        : type(t), id(newid), x(newx), y(newy), health(h), dir(d) {tank = nullptr; projectile = nullptr;};
    Tile(const Tile &tTile);
    ~Tile(){};
};
std::ostream & operator<<(std::ostream& os, const Tile& tile);
#endif
