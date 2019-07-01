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
    else if (tile.actor != nullptr)
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
    if (actor != nullptr){
        actor = std::unique_ptr<Tile>(new Tile(tTile.actor->type, tTile.actor->id, tTile.actor->x, tTile.actor->y, tTile.actor->health));
    }else{
        actor = nullptr;
    }
    if (projectile != nullptr){
        projectile = std::unique_ptr<Tile>(new Tile(tTile.projectile->type, tTile.projectile->id, tTile.projectile->x, tTile.projectile->y, tTile.projectile->health));
    }else{
        projectile = nullptr;
    }
}