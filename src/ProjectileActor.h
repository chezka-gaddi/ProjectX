//
// Created by jlee on 9/8/18.
//

#ifndef SLACKERS_PLATFORM_PROJECTILEACTOR_H
#define SLACKERS_PLATFORM_PROJECTILEACTOR_H

#include "Actor.h"

class ProjectileActor:public Actor{
protected:
    int range;
    int startX;
    int startY;
    int endX;
    int endY;
    int newX;
    int newY;
public:
    ProjectileActor();
    ProjectileActor(int, int, int, int, int);

    MoveData move();

    AttackData attack();

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
