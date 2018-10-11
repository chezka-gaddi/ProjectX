#ifndef __SIMPLE_AI_H
#define __SIMPLE_AI_H

#include "Actor.h"
#include "direction.h"


class SimpleAI : public Actor{
    
public:
    #ifndef testing

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(MapData map, PositionData status);

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual AttackData attack(MapData map, PositionData status);


    SimpleAI();
    ~SimpleAI();
    #endif
};

#endif
