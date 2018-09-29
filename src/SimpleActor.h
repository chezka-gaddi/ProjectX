/**
 * SimpleActor.h
 * a simple actor class with an 'AI' of:
 *   -Move up
 *   -Attack 0,0
 */

/** @file */

#ifndef __SIMPLE_ACTOR_H
#define __SIMPLE_ACTOR_H

#include "Actor.h"
#include "direction.h"

class SimpleActor : public Actor
{
public:
    virtual direction move(MapData map, PositionData status);
    virtual AttackData attack(MapData map, PositionData status);

};




#endif
