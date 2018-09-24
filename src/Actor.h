/***********************************************************
 * @file
 * @brief
 * This is the header file for the Actor class.
 *
 **********************************************************/
#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H


#include <string>
#include "MoveData.h"
#include "AttackData.h"

/*!
 * @brief This parent class will be inherited by every pojectile and tank
 */
class Actor{
protected:
    std::string name; // The string name of the actor
    int id; // the id number of the actor

public:
    #ifndef testing
    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual MoveData move(MapData map, PositionData status) = 0;
    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual AttackData attack(MapData map, PositionData status) = 0;
    #endif

    Actor();
    Actor(std::string newName, int newId);
    ~Actor();

    std::string getName();
    int getId();
    void setName(std::string newName);
    void setId(int newId);
};
#endif //SLACKERS_PLATFORM_ACTOR_H
