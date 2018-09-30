
/*******************************************************//**
 * @file
 *
 * @brief
 * This is the header file for the AsciiTankActor class
 *
 ************************************************************/

#ifndef	ASCIITANKACTOR_H
#define ASCIITANKACTOR_H

#include "Actor.h"

class AsciiTankActor : public Actor
{

      direction actorMove; 
      AttackData actorAttack;
public:
      virtual direction move(MapData map, PositionData status);    /*!<Returns the actorMove member variable */
      virtual AttackData attack(MapData map, PositionData status); /*!<Returns the actorAttack member variable */
      void setMove( direction decision );             /*!<Sets the actorMove object*/
      void setAttackData( int xAttack, int yAttack, int numDamage); /*!<Set the actorAttack object */
};

#endif
