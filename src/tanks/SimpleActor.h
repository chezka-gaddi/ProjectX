
/**
 * SimpleActor.h
 * a simple actor class with an 'AI' of:
 *   -Move up
 *   -Attack 0,0
 */

#ifndef __SIMPLE_ACTOR_H
#define __SIMPLE_ACTOR_H

#include <actors/Actor.h>
#include <structures/direction.h>
#include <iostream>

class SimpleActor : public Actor
{
    direction atk;
    direction dir;
    
    public:
        virtual direction move(const MapData &map, PositionData status);
        virtual direction attack(const MapData &map, PositionData status);
        virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
        virtual int spendAP(const MapData &map, PositionData status);
        SimpleActor();
        SimpleActor(direction mv, direction d);
        void setAttack(direction d);
        void setMove  (direction d);
};

#endif
