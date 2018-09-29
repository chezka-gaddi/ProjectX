////////////////////////////////////////////////////////////////////////////////
// File name: projectile_functional_tests.cpp
// Author: Adam Lenox
// Description: This file will test the projectile, directions, range, 
// projectile to projectile collisions, movement, wall to projectile collision
// projectile hit and miss.
// 
// Date: 27 Sep 18
////////////////////////////////////////////////////////////////////////////////

// Include(s)
#include <catch.hpp>
#include <GameField.h>
#include <AsciiTankActor.h>
#include <vector>
#include <iostream>
#include <catch.hpp>

////////////////////////////////////////////////////////////////////////////////
// FEATURE:
//    The projectiles can move around the game field and react with walls and
//    tanks and other projectiles.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Single projectile basic Movement, hit the wall on 2nd turn
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The projectile moves around the gamefield")
{
   GIVEN("A tank and a vertical gamefield")
   {
      // Create tank
      AsciiTankActor * tank = nullptr;
      Tank = new AsciiTankActor();
      REQUIRE(Tank != nullptr);

      // Load a tank
      ActorInfo tank_s(tank, 100,0,0,6,2);

      //Add a tank into a vector of actors
      std::vector<ActorInfo> actor_list = {tank_s};
     
      // Add a projectile into a vector of actors
      //std::vector<ActorInfo> actor_list = {projectile_s};
            	
      // Generate the gamefield with a map that looks like this:
      // 0
      // 0
      // 0
      // 0
      // 0
      // 0
      // 2
      // 0
      // 0
      // 0
      // 0
      // 0
      // 0
      GameField gamefield(0, 12, actor_list);
      
      WHEN("The tank tries to shoot up")
	{
	    tank->setAttack(0,0);
            tank->setMove('p');
            gamefield.nextTurn();
      THEN("The projectile goes up")
          {
	    //compare actual map to expected map
	    std::vector<int> expected_map = {-2, 0, 0, 0,
                                              0, 0, 2, 0, 
                                              0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
          } 
	    gamefield.nexturn();
      THEN("The projectile hits the wall")
	  {
	    //compare actual map to expected map
	    std::vector<int> expected_map = { 0, 0, 0, 0,
                                              0, 0, 2, 0, 
                                              0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
	  }
         }
      

      WHEN("The tank tries attacks to down")
        {
         tank->setAttack(0,12);
         tank->setMove('p');
         gamefield.nextTurn();

         THEN("The tank shoots down")
         {
            //Compare map with the initial map
            std::vector<int> expected_map = { 0, 0, 0, 0,
                                           0, 0, 2, 0,
                                           0, 0, 0, 0, -2 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);

	 }
	    gamefield.nexturn();
         THEN("The projectile hits the wall")
	  {
	    //compare actual map to expected map
	    std::vector<int> expected_map = { 0, 0, 0, 0,
                                              0, 0, 2, 0, 
                                              0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
	  }
        }
     }
   GIVEN("A tank and a horizontal gamefield")
   {
      // Create tank
      AsciiTankActor * tank = nullptr;
      Tank = new AsciiTankActor();
      REQUIRE(Tank != nullptr);

      // Load a tank
      ActorInfo tank_s(tank, 100,0,0,6,2);

      //Add a tank into a vector of actors
      std::vector<ActorInfo> actor_list = {tank_s};
     
      // Add a projectile into a vector of actors
      //std::vector<ActorInfo> actor_list = {projectile_s};
            	
      // Generate the gamefield with a map that looks like this:
      // 0,0,0,0,0,0,0,0,0,0,0,0,0
      GameField gamefield(12,0, actor_list);
      
      WHEN("The tank tries to shoot left")
	{
	    tank->setAttack(0,0);
            tank->setMove('p');
            gamefield.nextTurn();
      THEN("The projectile goes left")
          {
	    //compare actual map to expected map
	    std::vector<int> expected_map = {-2, 0, 0, 0,
                                              0, 0, 2, 0, 
                                              0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
          } 
            gamefield.nextTurn();
         THEN("The projectile hits the wall")
	  {
	    //compare actual map to expected map
	    std::vector<int> expected_map = { 0, 0, 0, 0,
                                              0, 0, 2, 0, 
                                              0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
	  }
         }
      

      WHEN("The tank tries attacks to right")
        {
         tank->setAttack(12,0);
         tank->setMove('p');
         gamefield.nextTurn();

         THEN("The projectile goes right")
         {
            //Compare map with the initial map
            std::vector<int> expected_map = { 0, 0, 0, 0,
                                              0, 0, 2, 0,
                                              0, 0, 0, 0, -2 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);

	 }
            gamefield.nextTurn();
         THEN("The projectile hits the wall")
	  {
	    //compare actual map to expected map
	    std::vector<int> expected_map = { 0, 0, 0, 0,
                                              0, 0, 2, 0, 
                                              0, 0, 0, 0, 0 };

            std::vector<int> actual_map = gamefield.getMap();
            REQUIRE(expected_map == actual_map);
	  }
        }
     }
}



