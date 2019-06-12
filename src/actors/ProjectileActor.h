//
// Created by jlee on 9/8/18.
//

/** @file */

#ifndef SLACKERS_PLATFORM_PROJECTILEACTOR_H
#define SLACKERS_PLATFORM_PROJECTILEACTOR_H

#include <cmath>
#include <actors/Actor.h>
#include <structures/direction.h>
#include <structures/MoveData.h>
#include <structures/attributes.h>

/*!
 * @brief This class is the base class for all projectile actors
 */
class ProjectileActor:public Actor
{
protected:
    std::string name = "projectile"; 
    direction dir;
public:
    ProjectileActor();
    ProjectileActor(direction d);

    direction move(MapData map, PositionData status);
    direction attack(MapData map, PositionData status);  
    attributes setAttribute(int pointsAvailable, attributes baseStats);
    int spendAP(MapData map, PositionData status);
};


#endif //SLACKERS_PLATFORM_PROJECTILEACTOR_H
