//
// Created by jlee on 9/8/18.
//

#ifndef SLACKERS_PLATFORM_PROJECTILEACTOR_H
#define SLACKERS_PLATFORM_PROJECTILEACTOR_H

#include "Actor.h"
#include <cmath>
class ProjectileActor:public Actor{
protected:
    int range;
    int startX;
    int startY;
    int endX;
    int endY;
public:
    ProjectileActor();

    MoveData move() override;

    AttackData attack() override;

    //Getters
int ProjectileActor::getRange();
int ProjectileActor::getStartX();
int ProjectileActor::getStartY();
int ProjectileActor::getEndX();
int ProjectileActor::getEndY();
//Setters
void ProjectileActor::setRange(int rangeUpdate);
void ProjectileActor::setStartX(int startXUpdate);
void ProjectileActor::setStartY(int startYUpdate);
void ProjectileActor::setEndX(int endXUpdate);
void ProjectileActor::setEndY(int endYUpdate);
};


#endif //SLACKERS_PLATFORM_PROJECTILEACTOR_H
