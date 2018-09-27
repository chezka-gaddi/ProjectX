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
#include <AsciiTankActor.h>
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// FEATURE:
//    The tanks can move around the game field and react with walls and
//    other tanks.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Single tank basic Movement
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The tank moves around the gamefied")
{
   GIVEN("A tank and a working gamefield")
   {
      // Create Tank
      AsciiTankActor * tank = nullptr;
      tank = new AsciiTankActor();
      REQUIRE(tank != nullptr);

      // Load Tanks
      ActorInfo   tank_s(tank, 100, 0, 1, 1, 2);

      std::vector<ActorInfo> actor_list = {tank_s};

      // Load Map



      // Add a tank into a vector of actors

      GameField gamefield(3, 3, actor_list);

      WHEN("The tank tries to move up")
      {
         tank->setMove('w');
         gamefield.nextTurn();

         THEN("The tank moves up")
         {
            //Compare map with the initial map
            std::vector<int> expected_map = { 0, 2, 0, 0, 0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }

      WHEN("The tank tries to move down")
      {
         std::vector<int> expected_map = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };

         std::vector<int> actual_map = gamefield.getMap();
         REQUIRE(expected_map == actual_map);
         tank->setMove('s');
         gamefield.nextTurn();

         THEN("The tank moves down")
         {
            //Compare map with the initial map
            std::vector<int> expected_map = { 0, 0, 0, 0, 0, 0, 0, 2, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }
      
      WHEN("The tank tries to move right")
      {
         std::vector<int> expected_map = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };

         std::vector<int> actual_map = gamefield.getMap();
         REQUIRE(expected_map == actual_map);
         tank->setMove('d');
         gamefield.nextTurn();
         THEN("The tank moves right")
         {
            //Compare map with the initial map
            std::vector<int> expected_map = { 0, 0, 0, 0, 0, 2, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }

      WHEN("The tank tries to move left")
      {
         std::vector<int> expected_map = { 0, 0, 0, 0, 2, 0, 0, 0, 0 };

         std::vector<int> actual_map = gamefield.getMap();
         REQUIRE(expected_map == actual_map);
         tank->setMove('a');
         gamefield.nextTurn();
         THEN("The tank moves left")
         {
            //Compare map with the initial map
            std::vector<int> expected_map = { 0, 0, 0, 2, 0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
// Hitting Wall Boundries
////////////////////////////////////////////////////////////////////////////////

SCENARIO("The tank encounters a wall")
{
   GIVEN("A tank and a gamefield")
   {
      // Create Tank
      AsciiTankActor * tank = nullptr;
      tank = new AsciiTankActor();
      REQUIRE(tank != nullptr);

      // Load Tanks
      ActorInfo   tank_s(tank, 100, 0, 0, 0, 2);

      std::vector<ActorInfo> actor_list = {tank_s};

      // Load Map



      // Add a tank into a vector of actors

      GameField gamefield(1, 1, actor_list);

   
      WHEN("A tank hits a wall going up")
      {
         tank->setMove('w');
         gamefield.nextTurn();
         THEN("The tank cannot move up anymore")
         {
            std::vector<int> expected_map = { 2 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }

      WHEN("A tank hits a wall going left")
      {
         tank->setMove('a');
         gamefield.nextTurn();
         THEN("The tank cannot move up anymore")
         {
            std::vector<int> expected_map = { 2 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }

      WHEN("A tank hits a wall going right")
      {
         tank->setMove('d');
         gamefield.nextTurn();
         THEN("The tank cannot move up anymore")
         {
            std::vector<int> expected_map = { 2 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }

      WHEN("A tank hits a wall going down")
      {
         tank->setMove('s');
         gamefield.nextTurn();
         THEN("The tank cannot move up anymore")
         {
            std::vector<int> expected_map = { 2 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
         }
      }

   }
}

////////////////////////////////////////////////////////////////////////////////
// Tank Collision Test
////////////////////////////////////////////////////////////////////////////////

SCENARIO("Tanks drive right into each other")
{
   GIVEN("A 3 x 1 Game Field with two tanks")
   {
      AsciiTankActor * tank_1 = nullptr;
      AsciiTankActor * tank_2 = nullptr;

      tank_1 = new AsciiTankActor();
      tank_2 = new AsciiTankActor();
      
      ActorInfo tank_1_s(tank_1, 100, 1000, 0, 0, 1);
      ActorInfo tank_2_s(tank_2, 100, 1000, 2, 0, 2);

      std::vector<ActorInfo> actor_list = {tank_1_s, tank_2_s};

      GameField gamefield(3, 1, actor_list);

      // WHEN("Tanks try to move into the same spot")
      {
         tank_1->setMove('d');
         tank_2->setMove('a');
         gamefield.nextTurn();
         //THEN("Both tanks die!")
         {
             REQUIRE(gamefield.getActors()[0].health == 0);
         }
      }

   }
}
