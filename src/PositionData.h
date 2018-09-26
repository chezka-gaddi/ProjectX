//
// Created by jlee on 9/8/18.
//

#ifndef SLACKERS_PLATFORM_POSITIONDATA_H
#define SLACKERS_PLATFORM_POSITIONDATA_H

#include "direction.h"
#include "string"
struct PositionData{

    std::string name; //identifying info
    int id; //identifying info,
    int health; //0 the tank is destroyed
    int game_x;
    int game_y;
    direction heading;

};
#endif //SLACKERS_PLATFORM_POSITIONDATA_H
