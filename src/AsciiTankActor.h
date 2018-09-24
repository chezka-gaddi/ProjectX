#ifndef	ASCIITANKACTOR_H
#define ASCIITANKACTOR_H

#include "TankActor.h"
#include "MoveData.h"
#include "PositionData.h"
#include "AttackData.h"

class AsciiTankActor : public Actor
{
   public:
      AsciiTankActor();
      MoveData move();
      AttackData attack();
};

#endif
