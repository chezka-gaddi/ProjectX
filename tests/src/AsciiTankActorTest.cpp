#include "catch.hpp"
#include <AsciiTankActor.h>
#include <Actor-Alternate.h>

using namespace std;

TEST_CASE("Create an AsciiTankActor object.")
{
   AsciiTankActor tank;
   REQUIRE( sizeof(tank) > 0 ); 
}

TEST_CASE("Check if move() returns right directions")
{
   AsciiTankActor tank;
   direction test1;
   direction test2;
   direction test3;
   direction test4;
   direction test5;
   direction test6;

   MapData m;
   PositionData p;

   test1 = tank.move(m,p);
   test2 = tank.move(m,p);
   test3 = tank.move(m,p);
   test4 = tank.move(m,p);
   test5 = tank.move(m,p);
   test6 = tank.move(m,p);

   REQUIRE ( test1 == 0 );
   REQUIRE ( test2 == 1 );
   REQUIRE ( test3 == 2 );
   REQUIRE ( test4 == 3 );
   REQUIRE ( test5 == 4 );
   REQUIRE ( test6 == 4 );
}

TEST_CASE("Check if attack() will return entered coordinates")
{
   AsciiTankActor tank;
   MapData m;
   PositionData p;
   AttackData test1;

   test1 = tank.attack(m,p);
   
   REQUIRE ( test1.attack_x == 1 );
   REQUIRE ( test1.attack_y == 1 );
   REQUIRE ( test1.damage == 1 );
}
