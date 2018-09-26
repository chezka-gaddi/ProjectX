#include "catch.hpp"
#include <AsciiTankActor.h>
#include <Actor-Alternate.h>

using namespace std;

TEST_CASE("Create an AsciiTankActor object.")
{
   AsciiTankActor tank;
<<<<<<< HEAD
   tank.move( 1, 9);
=======
   REQUIRE( sizeof(tank) > 0 ); 
}

TEST_CASE("Check if move() returns right directions")
{
   AsciiTankActor tank;
   MapData m;
   PositionData p;

   tank.setMove('a');
   REQUIRE(tank.move(m,p) == 0);
   
   tank.setMove('d');
   REQUIRE(tank.move(m,p) == 1);

   tank.setMove('w');
   REQUIRE(tank.move(m,p) == 2);

   tank.setMove('s');
   REQUIRE(tank.move(m,p) == 3);

   tank.setMove('p');
   REQUIRE(tank.move(m,p) == 4);

   tank.setMove('j');
   REQUIRE(tank.move(m,p) == 4);
>>>>>>> b9c68709e507d092236334e4860117d0519788b3
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

