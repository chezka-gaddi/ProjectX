////////////////////////////////////////////////////////////////////////////////
// File name: movement_test.cpp
// Author: Riley Kopp
// Description: This file will test the movement of the tank across the 
//              gamefield.
// Date: 19 Sep 18
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <catch.hpp>
#include <GameField.h>
#include <SimpleActor.h>
#include <vector>


SCENARIO("The tank moves around the gamefied")
{
   GIVEN("A tank and a working gamefield")
   {
      // Create Tank
      SimpleActor * tank = nullptr;
      tank = new SimpleActor();
      REQUIRE(tank != nullptr);

      // Load Tanks
      ActorInfo   tank_s(tank, 100, 1, 1, 1, 0);

      std::vector<ActorInfo> actor_list = {tank_s};

      // Load Map
      std::vector<int> map = {



      // Add a tank into a vector of actors

      GameField gamefield(10, 10, actor_list);

      WHEN("The tank tries to move up")
      {
         gamefield.
         THEN("The tank moves up")
         {
            //Compare map with the initial map
            REQUIRE(true == true);
         }
      }

      WHEN("The tank tries to move down")
      {
         //tank.down()
         THEN("The tank moves down")
         {
            REQUIRE(true == true);
            //Compare map with the initial map
         }
      }
      
      WHEN("The tank tries to move left")
      {
         //tank.left()
         THEN("The tank moves left")
         {
            //Compare map with the initial map
            REQUIRE(true == true);
         }
      }

      WHEN("The tank tries to move right")
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
