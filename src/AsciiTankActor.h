#ifndef	ASCIITANKACTOR_H
#define ASCIITANKACTOR_H

#include "Actor-Alternate.h"

class AsciiTankActor : public Actor
{

      direction actorMove;
      AttackData actorAttack;
public:
      virtual direction move(MapData map, PositionData status);
      virtual AttackData attack(MapData map, PositionData status);
      void setMove( direction decision );
      void setAttackData( int xAttack, int yAttack, int numDamage);
};

#endif
