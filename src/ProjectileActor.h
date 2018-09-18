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
public:
    ProjectileActor();

    MoveData move() override;

    AttackData attack() override;
};


#endif //SLACKERS_PLATFORM_PROJECTILEACTOR_H
