#include "Tile.h"

std::ostream & operator<<(std::ostream& os, const Tile& tile){
    std::string tType = tile.type;
    
    if(tType == "Rock")
        os << "R";
    else if (tType == "Water")
        os << "W";
    else if (tType == "Bush")
        os << "B";
    else if (tType == "Tree")
        os << "T";
    else if (tType == "Crate")
        os << "C";
    else if (tType == "Hedgehog")
        os << "H";
    else if (tile.tank != nullptr)
        os << "¤";
    else if (tile.projectile != nullptr)
        os << "º";
    else 
        os << "x";
    
    return os;
}

Tile::Tile(const Tile & tTile){
    type = tTile.type;
    id = tTile.id;
    x = tTile.x;
    y = tTile.y;
    health = tTile.health;
    if (tank != nullptr){
        tank = std::unique_ptr<Tile>(new Tile(tTile.tank->type, tTile.tank->id, tTile.tank->x, tTile.tank->y, tTile.tank->health, tTile.tank->dir));
    }else{
        tank = nullptr;
    }
    if (projectile != nullptr){
        projectile = std::unique_ptr<Tile>(new Tile(tTile.projectile->type, tTile.projectile->id, tTile.projectile->x, tTile.projectile->y, tTile.projectile->health, tTile.projectile->dir));
    }else{
        projectile = nullptr;
    }
}