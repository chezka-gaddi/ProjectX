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
      ActorInfo tank_s(tank, 100,0,6,0,2);

      //Add a tank into a vector of actors
      std::vector<ActorInfo> actor_list = {tank_s};
     
      // Add a projectile into a vector of actors
      //std::vector<ActorInfo> actor_list = {projectile_s};
            	
      // Generate the gamefield with a map that looks like this:
      // 0,0,0,0,0,0,2,0,0,0,0,0,0
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
////////////////////////////////////////////////////////////////////////////////
// Projectiles can collide with each other and can be spawned from 
// 2 tanks on the field, projectiles deal damage to a tank when the tank is hit.
//
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The projectile collides with the actors on the gamefield")
{
      // Create 2 tanks
      AsciiTankActor * tank = nullptr;
      tank = new AsciiTankActor();
      REQUIRE(tank != nullptr);

      AsciiTankActor * tank2 = nullptr;
      tank2 = new AsciiTankActor();
      REQUIRE(tank2 != nullptr);

      // Load a tank
      ActorInfo tank_s(tank, 100,0,13,0,2);
      ActorInfo tank_q(tank2, 100,0,0,0,3);

      //Add a tank into a vector of actors
      std::vector<ActorInfo> actor_list = {tank_s,tank_q};
     
      // Add a projectile into a vector of actors
      //std::vector<ActorInfo> actor_list = {projectile_s};
            	
      // Generate the gamefield with a map that looks like this:
      // 3,0,0,0,0,0,0,0,0,0,0,0,0,2

      GameField gamefield(13,0, actor_list);
	GIVEN("A horizontal gamefeild and two tanks")
	{
		WHEN("Each tank tries to shoot a projectile")
		{
		     tank->setAttack(0,0);//attack 2nd
         	     tank->setMove('p');
		     tank2->setAttack(13,0);//attack 1st
         	     tank2->setMove('p');
         	     gamefield.nextTurn();

			THEN("The projectiles spawn and travle their range")
			{
			     //Compare map with the initial map
            		     std::vector<int> expected_map = { 3, 0, 0, 0, 0, 0, -3, -2, 0, 0, 0, 0, 0, 2 };

            		     std::vector<int> actual_map = gamefield.getMap();
            		     REQUIRE(expected_map == actual_map);
			}

         	     gamefield.nextTurn();

			THEN("The projectiles collide and despawn")
			{
			     std::vector<int> expected_map = { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 };
            		     std::vector<int> actual_map = gamefield.getMap();
            		     REQUIRE(expected_map == actual_map);
			}
		}
		
		WHEN("One tank shoots at the other tank and the other tank does not move")
		{
         	     tank->setMove('p');//do not move
		     tank2->setAttack(13,0);//attack 1st
         	     tank2->setMove('p');
         	     gamefield.nextTurn();
         	     gamefield.nextTurn();
         	     gamefield.nextTurn();

			THEN("The second tank is hit and the tank takes damage")
			{
				require(tank.health == 99);
			}
		}
	}
}



