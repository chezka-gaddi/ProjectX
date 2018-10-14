/**
 * SimpleActor.h
 * a simple actor class with an 'AI' of:
 *   -Move up
 *   -Attack 0,0
 */

#ifndef __SIMPLE_ACTOR_H
#define __SIMPLE_ACTOR_H

#include "Actor.h"
#include "direction.h"

class SimpleActor : public Actor
{
    direction dir;
    AttackData atk;
    
    public:
        virtual direction move(MapData map, PositionData status);
        virtual AttackData attack(MapData map, PositionData status);
        SimpleActor();
        SimpleActor(direction mv, int d);
        void setAttack(int x, int y, int d);
        void setMove  (direction d);
};

#endif
