#ifndef __PONG_AI_H
#define __PONG_AI_H

#include "Actor.h"
#include "direction.h"
#include <cmath>
#include <iostream>

class PongAI : public Actor
{
   /**
     * calculates how many moves it will take to reach a given coordinate
     * @param[in] x1 - starting point x coordinate
     * @param[in] y1 - starting point y coordinate
     * @param[in] x2 - end point x coordinate
     * @param[in] y2 - end point y coordinate
     * @return distance to the target
     */
    /**
     * The direction that the tank used last
     */
    direction LastDir;
    std::vector<bool> nogo_map;
    bool next(std::vector<bool> target_map
            , direction         attempted_move
            , MapData           map
            , PositionData      status);

public:

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(MapData map, PositionData status);

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual direction attack(MapData map, PositionData status);

    virtual attributes setAttribute(int pointsAvailable);

    virtual int spendAP(MapData map, PositionData status);

    PongAI();
    ~PongAI();
};

#endif
