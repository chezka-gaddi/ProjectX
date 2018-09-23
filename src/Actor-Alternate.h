/** Actor-Alternate.h
 *  This is a temporary version of Actor.h that I am using to test the GameFeild class. Once Actor.h is updated,
 *  this file will be obsolete.
 */
#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H


#include "PositionData.h"
#include "AttackData.h"
#include "direction.h"
#include "MapData.h"
#include <string>
#include <vector>


class Actor{
    std::string name;

public:
    
    virtual direction move(MapData map, PositionData status) = 0;
    virtual AttackData attack(MapData map, PositionData status) = 0;

    void setName(std::string newName);
};

#endif
    
