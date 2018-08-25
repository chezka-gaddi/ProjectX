//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H

#include "GameField.h"


//this is a parent class for all classes that do something on the playing field
class Actor{
protected:
    //playing field position this could be different from the screen position depending on the direction the project goes
    int field_x, field_y;

public:
    ///
    /// \param gameField the current game field that the actor is on
    virtual void move(GameField &gameField) = 0; //essentially a tick function, but since the game is turn based one move = one tick

};
#endif //SLACKERS_PLATFORM_ACTOR_H
