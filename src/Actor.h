//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H


#include <string>
#include "MoveData.h"
#include "AttackData.h"
//this is a parent class for all classes that do something on the playing field
class Actor{
protected:
    std::string name;
    int id;// the id of the actor, so that data can be connected between drawing and game logic
    //playing field position this could be different from the screen position depending on the direction the project goes
    int field_x, field_y;

    int health;// health of the actor positive values will be normal, negative values will be special cases

    int damage;//damage of the actor for tanks it is the damage done when firing for projectiles it is damage done on hit

public:
    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual MoveData move() = 0;
    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual AttackData attack() = 0;

    /*******************************/
    /*************getters***********/
    /*******************************/




    /*******************************/
    /************setters************/
    /*******************************/
};
#endif //SLACKERS_PLATFORM_ACTOR_H
