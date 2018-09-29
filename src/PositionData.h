//
// Created by jlee on 9/8/18.
//

/** @file */

#ifndef SLACKERS_PLATFORM_POSITIONDATA_H
#define SLACKERS_PLATFORM_POSITIONDATA_H

#include "direction.h"
#include "string"
struct PositionData{

    std::string name; /*!<The name */  
    int id; /*!<The id number */  
    int health; /*!<The health */
    int game_x; /*!<The x coordinate */
    int game_y; /*!<The y coordinate */
    direction heading; /*!<The heading direction */

};
#endif //SLACKERS_PLATFORM_POSITIONDATA_H
