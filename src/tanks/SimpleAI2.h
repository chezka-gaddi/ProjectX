#ifndef __SIMPLE_AI2_H
#define __SIMPLE_AI2_H

#include <actors/Actor.h>
#include <structures/direction.h>
#include <cmath>

class SimpleAI2 : public Actor
{
    int calcDist(int x1, int y1, int x2, int y2);

public:
#ifndef testing

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(const MapData &map, PositionData status);

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual direction attack(const MapData &map, PositionData status);

    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);

    virtual int spendAP(const MapData &map, PositionData status);
    /**
     * calculates how many moves it will take to reach a given coordinate
     * @param[in] x1 - starting point x coordinate
     * @param[in] y1 - starting point y coordinate
     * @param[in] x2 - end point x coordinate
     * @param[in] y2 - end point y coordinate
     * @return distance to the target
     */
   
    attributes myStats; 
  
    bool spend = false;

    SimpleAI2();
    ~SimpleAI2();
#endif
};

#endif
