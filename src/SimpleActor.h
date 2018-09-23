/**
 * SimpleActor.h
 * a simple actor class with an 'AI' of:
 *   -Move up
 *   -Attack 0,0
 */

#ifndef __SIMPLE_ACTOR_H
#define __SIMPLE_ACTOR_H

#include "Actor-Alternate.h"

class SimpleActor : public Actor
{
    virtual direction move(MapData map, PositionData status);
    virtual AttackData attack(MapData map, PositionData status);

};




#endif
