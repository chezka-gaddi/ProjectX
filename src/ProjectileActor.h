//
// Created by jlee on 9/8/18.
//

/** @file */

#ifndef SLACKERS_PLATFORM_PROJECTILEACTOR_H
#define SLACKERS_PLATFORM_PROJECTILEACTOR_H

#include <cmath>
#include "Actor.h"
#include "direction.h"
#include "MoveData.h"
#include "AttackData.h"

/*!
 * @brief This class is the base class for all projectile actors
 */
class ProjectileActor:public Actor{
protected:
    int range;     /*!<The range of the projectile */
    int startX;    /*!<The starting x coordinate */
    int startY;    /*!<The starting y coordinate */
    int endX;     /*!<The ending x coordinate */
    int endY;     /*!<The ending y coordinate */
    int newX;     /*!<The new x coordinate */
    int newY;     /*!<The new y coordinate */
public:
    ProjectileActor();
    ProjectileActor(int newRange, int newStartX, int newStartY, int newEndX,
                    int newEndY);

    direction move(MapData map, PositionData status);

    AttackData attack(MapData map, PositionData status);  

    //Getters
    int getRange();    
    int getStartX();  
    int getStartY(); 
    int getEndX();  
    int getEndY(); 
    int getNewX();
    int getNewY();
    //Setters
    void setRange(int rangeUpdate);  
    void setStartX(int startXUpdate);
    void setStartY(int startYUpdate);
    void setEndX(int endXUpdate);    
    void setEndY(int endYUpdate);

};


#endif //SLACKERS_PLATFORM_PROJECTILEACTOR_H
