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

struct Tile{
    std::string type="Empty"; //{Rock, Bush, Tree, Water, Crate, Tank, Projectile}
    int id = 0;
    int x = 0;
    int y = 0;
    int health = 0;
    std::shared_ptr<Tile> actor;
    std::shared_ptr<Tile> projectile;
    //constructor with initial values
    Tile(std::string t="Empty", int newid=0, int newx=0, int newy=0, int h=0) 
        : type(t), id(newid), x(newx), y(newy), health(h) {actor = nullptr; projectile = nullptr;};
    Tile(const Tile &tTile);
    ~Tile(){};
};
std::ostream & operator<<(std::ostream& os, const Tile& tile);
#endif