//
// Created by jlee on 9/8/18.
//

#ifndef SLACKERS_PLATFORM_TANKACTOR_H
#define SLACKERS_PLATFORM_TANKACTOR_H

#include "Actor.h"

class TankActor : public Actor{

public:

    TankActor();

    MoveData move() override;

    AttackData attack() override;

    /*******************************/
    /********constructors***********/
    /*******************************/




    /*******************************/
    /*************getters***********/
    /*******************************/




    /*******************************/
    /************setters************/
    /*******************************/

};


#endif //SLACKERS_PLATFORM_TANKACTOR_H
