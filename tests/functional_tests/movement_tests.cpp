////////////////////////////////////////////////////////////////////////////////
// File name: movement_test.cpp
// Author: Riley Kopp
// Description: This file will test the movement of the tank across the 
//              gamefield.
// Date: 19 Sep 18
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <catch.hpp>


SCENARIO("The tank moves around the gamefied")
{
   GIVEN("A tank and a working gamefield")
   {
      // Initialize game field
      // Slackers()
      //
      // Load Tanks
      // Add_Tank(test_tank)
      //
      // Add map that looks like this:
      // wwwwwwwwwww
      // w         w
      // w    t    w
      // w         w
      // wwwwwwwwwww
      //

      WHEN("The tank ties to move up")
      {
         //tank.up()
         THEN("The tank moves up")
         {
            //Compare map with the initial map
            REQUIRE(true == true);
         }
      }

      WHEN("The tank ties to move down")
      {
         //tank.down()
         THEN("The tank moves down")
         {
            REQUIRE(true == true);
            //Compare map with the initial map
         }
      }
      
      WHEN("The tank ties to move left")
      {
         //tank.left()
         THEN("The tank moves left")
         {
            //Compare map with the initial map
            REQUIRE(true == true);
         }
      }

      WHEN("The tank ties to move right")
      {
         //tank.right()
         THEN("The tank moves right")
         {
            //Compare map with the initial map
            REQUIRE(true == true);
         }
      }
   }
}


SCENARIO("The tank encounters a wall")
{
   GIVEN("A tank and a gamefield")
   {
      //Init Game Field
      //Platform()
      //
      //Add Tank
      //Add Tank(tank)
      //
      // Make a map that looks like this
      //    w
      //   wtw
      //    w
      // load custom map array
      // add_map(map)
      //
   
      WHEN("A tank hits a wall going up")
      {
         THEN("The tank cannot move up anymore")
         {
            //REQUIRE(tank.up() == false);
         }
      }

      WHEN("A tank hits a wall going left")
      {
         THEN("The tank cannot move left anymore")
         {
            //REQUIRE(tank.left() == false);
         }
      }

      WHEN("A tank hits a wall going right")
      {
         THEN("The tank cannot move right anymore")
         {
            //REQUIRE(tank.right() == false);
         }
      }

      WHEN("A tank hits a wall going down")
      {
         THEN("The tank cannot move down anymore")
         {
            //REQUIRE(tank.down() == false);
         }
      }

   }
}
