//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H

#include "GameField.h"
#include <string>

//this is a parent class for all classes that do something on the playing field
class Actor{
protected:
    std::string name;
    int id;
    //playing field position this could be different from the screen position depending on the direction the project goes
    int field_x, field_y;
    int health;// health of the actor
    int damage;//damage of the actor

public:
    ///
    /// \param gameField the current game field that the actor is on
    virtual void move(GameField &gameField) = 0;
    virtual void attack(GameField &gameField) = 0;
};
#endif //SLACKERS_PLATFORM_ACTOR_H
