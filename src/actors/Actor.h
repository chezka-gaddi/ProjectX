/** @file */

#ifndef SLACKERS_PLATFORM_ACTOR_H
#define SLACKERS_PLATFORM_ACTOR_H
#include <string>
#include <structures/attributes.h>
#include <map/MapData.h>
#include <structures/direction.h>
#include <structures/PositionData.h>

/*!
 * @brief This parent class will be inherited by every projectile and tank
 */
class Actor
{
protected:
    std::string name = "Hank the Tank";       /*!< The string name of the actor */
    int id = 0;                 /*!< the id number of the actor */

public:
    //Actor(){}; //Commented out to remove compaitibility errors
    virtual ~Actor()=0; /*!< Default deconstructor that must be overriden by custom tanks */

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(const MapData &map, PositionData status) = 0;

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual direction attack(const MapData &map, PositionData status) = 0;

    /**
     *  sets the attributes of the tank
     *  @return attributeStruct to set tanks attribute
     */
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats) = 0;

    /**
     *  Decides wether to move or attack given how many AP remain 
     *  @return 0 for end turn, 1 for move, 2 for attack
     */
    virtual int spendAP(const MapData &map, PositionData status) = 0;

    //Getters
    std::string getName();    /*!< Returns the value within name */
    int getId(); /*!< Returns the value within id */
    //Setters
    void setId(int newId); /*!< Sets the value of id to teh value in newId */
};
#endif //SLACKERS_PLATFORM_ACTOR_H
