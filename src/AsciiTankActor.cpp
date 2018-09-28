#include <iostream>
#include "AsciiTankActor.h"

using std::cout;
using std::cin;
using std::endl;

void AsciiTankActor::setMove( direction decision )
{
   actorMove = decision;

   return;
   
}

direction AsciiTankActor::move( MapData map, PositionData status)
{
   
   return actorMove;
}

void AsciiTankActor::setAttackData( int xAttack, int yAttack, int numDamage)
{
   actorAttack.attack_x = xAttack;
   actorAttack.attack_y = yAttack;
   actorAttack.damage = numDamage;
  
   return;
}

AttackData AsciiTankActor::attack( MapData map, PositionData status)
{
   return actorAttack;
}
