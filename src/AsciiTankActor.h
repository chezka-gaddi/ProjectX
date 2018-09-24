#ifndef	ASCIITANKACTOR_H
#define ASCIITANKACTOR_H

#include "Actor-Alternate.h"

class AsciiTankActor : public Actor
{
public:
      virtual direction move(MapData map, PositionData status);
      virtual AttackData attack(MapData map, PositionData status);
};

#endif
