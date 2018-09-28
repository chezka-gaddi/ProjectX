#include "catch.hpp"
#include <AsciiTankActor.h>
#include <Actor-Alternate.h>


TEST_CASE("Create an AsciiTankActor object.")
{
   AsciiTankActor tank;
   REQUIRE( sizeof(tank) > 0 ); 
}

TEST_CASE("Check if move() returns right directions")
{
   AsciiTankActor tank;
   MapData m;
   PositionData p;

   tank.setMove(left);
   REQUIRE(tank.move(m,p) == 0);
   
   tank.setMove(right);
   REQUIRE(tank.move(m,p) == 1);

   tank.setMove(up);
   REQUIRE(tank.move(m,p) == 2);

   tank.setMove(down);
   REQUIRE(tank.move(m,p) == 3);

   tank.setMove(stay);
   REQUIRE(tank.move(m,p) == 4);

}


TEST_CASE("Check if attack() will return entered coordinates")
{
   AsciiTankActor tank;
   MapData m;
   PositionData p;
   AttackData test1;

   tank.setAttackData( 1, 2, 3 );
   test1=tank.attack(m,p);
   
   REQUIRE ( test1.attack_x == 1 );
   REQUIRE ( test1.attack_y == 2 );
   REQUIRE ( test1.damage == 3 );
}

