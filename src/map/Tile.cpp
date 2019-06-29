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