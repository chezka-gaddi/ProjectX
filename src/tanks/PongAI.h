#ifndef __PONG_AI_H
#define __PONG_AI_H

#include <actors/Actor.h>
#include <structures/direction.h>
#include <cmath>
#include <iostream>


///////////////////////////////////////////////////////////////////////////////
/// Description: This AI acts like a paddle from pong. It will move vertically
//               and shoot each turn
///////////////////////////////////////////////////////////////////////////////


class PongAI : public Actor
{
    // The direction moved from last turn
    direction LastDir;

public:

    // The Overwritten Move function.
    virtual direction move(const MapData &map, PositionData status);

    // The Overwritten attack function.
    virtual direction attack(const MapData &map, PositionData status);

    // The Overwritten set attribute  function.
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);

    // The Overwritten spendAP  function.
    virtual int spendAP(const MapData &map, PositionData status);

    PongAI();
    ~PongAI();
};

#endif
