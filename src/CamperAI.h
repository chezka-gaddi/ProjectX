#ifndef __CAMPER_AI_H
#define __CAMPER_AI_H

#include "Actor.h"
#include "direction.h"
#include <cmath>
#include <iostream>


///////////////////////////////////////////////////////////////////////////////
/// Description: This AI finds a corner and starts shooting. It's like an 8
//                year old playing call of duty.
///////////////////////////////////////////////////////////////////////////////


class CamperAI : public Actor
{
    // The direction moved from last turn
    direction LastDir;

public:

    // The Overwritten Move function.
    virtual direction move(MapData map, PositionData status);

    // The Overwritten attack function.
    virtual direction attack(MapData map, PositionData status);

    // The Overwritten set attribute  function.
    virtual attributes setAttribute(int pointsAvailable);

    // The Overwritten spendAP  function.
    virtual int spendAP(MapData map, PositionData status);

    CamperAI();
    ~CamperAI();
};

#endif
