#include "Tile.h"

std::ostream & operator<<(std::ostream& os, const Tile& tile){
    std::string tType = tile.type;
    std::string sType = "";
    
    if (tile.actor != nullptr)
        sType = tile.actor->type;
    
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
    else if (tType == "Tank" || sType == "Tank")
        os << "¤";
    else if (tType == "Projectile" || sType == "Projectile")
        os << "º";
    else 
        os << "x";
    
    return os;
}