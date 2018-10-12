/** @file */

#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H


#include <string>
#include "MoveData.h"
#include "AttackData.h"
#include "MapData.h"
#include "direction.h"
#include "PositionData.h"

/*!
 * @brief This parent class will be inherited by every projectile and tank
 */
class Actor{
protected:
   std::string name;       /*!< The string name of the actor */
   int id;                 /*!< the id number of the actor */

public:
    #ifndef testing

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(MapData map, PositionData status) = 0;

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual AttackData attack(MapData map, PositionData status) = 0;

    #endif

    Actor();
    ~Actor();
    Actor(std::string newName, int newId);

    virtual //Getters
    std::string getName();    /*!< Returns the value within name */  
    int getId(); /*!< Returns the value within id */  
    //Setters   
    void setName(std::string newName);   /*!< Sets the value of name to the value in newName */  
    void setId(int newId); /*!< Sets the value of id to teh value in newId */  
};
#endif //SLACKERS_PLATFORM_ACTOR_H
