#ifndef	ASCIITANKACTOR_H
#define ASCIITANKACTOR_H

#include "TankActor.h"

class AsciiTankActor : public TankActor
{
   public:
      AsciiTankActor();
      MoveData move();
      AttackData attack();
};

#endif
