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
    else 
        os << "x";
    
    return os;
}