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
#include <vector>
#include <iostream>
#include <direction.h>
#include <SimpleActor.h>

////////////////////////////////////////////////////////////////////////////////
// FEATURE:
//    The tanks can move around the game field and react with walls and
//    other tanks.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Single tank basic Movement
////////////////////////////////////////////////////////////////////////////////
SCENARIO("The tank moves around the gamefield")
{
    GIVEN("A tank and a working gamefield")
    {
        // Create Tank
        SimpleActor * tank = nullptr;
        tank = new SimpleActor();
        direction moveUp = UP;
        direction moveDown = DOWN;
        direction moveLeft = LEFT;
        direction moveRight = RIGHT;
        direction moveStay = STAY;
        REQUIRE(tank != nullptr);

        // Load Tanks
        ActorInfo tank_s(tank, "a1", 1, 2, 2, 1, 1, 6, 2, 6, 6, 2, 2);

        // Add a tank into a vector of actors
        std::vector<ActorInfo> actor_list = {tank_s};

        // Generate the gamefield with a map that looks like this:
        // 000
        // 020
        // 000
        GameField gamefield(3, 3, actor_list, NULL, nullptr, nullptr);

        WHEN("The tank tries to move up")
        {
            tank->setMove(moveUp);
            tank->setAttack(STAY);
            gamefield.nextTurn();

            THEN("The tank moves up")
            {
                //Compare map with the initial map
                REQUIRE(gamefield.fieldMap->tileMap[1][2].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[2][2].actor == nullptr);
            }
        }

        WHEN("The tank tries to move down")
        {
            gamefield.updateMap();
            CHECK(gamefield.fieldMap->tileMap[2][2].actor != nullptr);

            tank->setMove(moveDown);
            gamefield.nextTurn();

            THEN("The tank moves down")
            {
                //Compare map with the initial map
                REQUIRE(gamefield.fieldMap->tileMap[3][2].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[2][2].actor == nullptr);
            }
        }

        WHEN("The tank tries to move right")
        {
            gamefield.updateMap();
            REQUIRE(gamefield.fieldMap->tileMap[2][2].actor != nullptr);
            
            tank->setMove(moveRight);
            gamefield.nextTurn();
            THEN("The tank moves right")
            {
                REQUIRE(gamefield.fieldMap->tileMap[2][3].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[2][2].actor == nullptr);
            }
        }

        WHEN("The tank tries to move left")
        {
            gamefield.updateMap();
            REQUIRE(gamefield.fieldMap->tileMap[2][2].actor != nullptr);

            tank->setMove(moveLeft);
            gamefield.nextTurn();
            THEN("The tank moves left")
            {
                REQUIRE(gamefield.fieldMap->tileMap[2][1].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[2][2].actor == nullptr);
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
        SimpleActor * tank = nullptr;
        tank = new SimpleActor();

        direction moveUp = UP;
        direction moveDown = DOWN;
        direction moveLeft = LEFT;
        direction moveRight = RIGHT;
        direction moveStay = STAY;
        REQUIRE(tank != nullptr);

        // Load Tanks
        ActorInfo   tank_s(tank, "a1", 1, 1, 1, 2, 2, 2, 2, 5, 5, 2, 2);

        // Add a tank into a vector of actors
        std::vector<ActorInfo> actor_list = {tank_s};

        // Generate the gamefield with a map that looks like this:
        // 2
        GameField gamefield(1, 1, actor_list, NULL, nullptr, nullptr);
        gamefield.updateMap();
        REQUIRE(gamefield.fieldMap->tileMap[1][1].actor != nullptr);

        WHEN("A tank hits a wall going up")
        {
            tank->setMove(moveUp);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor->health == 1);
            }
        }

        WHEN("A tank hits a wall going left")
        {
            tank->setMove(moveLeft);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor->health == 1);
            }
        }

        WHEN("A tank hits a wall going right")
        {
            tank->setMove(moveRight);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor->health == 1);
            }
        }

        WHEN("A tank hits a wall going down")
        {
            tank->setMove(moveDown);
            gamefield.nextTurn();
            THEN("The tank cannot move up anymore")
            {
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor != nullptr);
                REQUIRE(gamefield.fieldMap->tileMap[1][1].actor->health == 1);
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
        SimpleActor * tank_1 = nullptr;
        SimpleActor * tank_2 = nullptr;

        direction moveRight = RIGHT;
        direction moveLeft = LEFT;

        tank_1 = new SimpleActor();
        tank_2 = new SimpleActor();

        ActorInfo tank_1_s(tank_1, "a1", 1, 1, 1, 10, 10, 4, 2, 4, 4, 2, 2);
        ActorInfo tank_2_s(tank_2, "a2", 2, 3, 1, 10, 10, 4, 2, 4, 4, 2, 2);

        std::vector<ActorInfo> actor_list = {tank_1_s, tank_2_s};

        GameField gamefield(3, 1, actor_list, NULL, nullptr, nullptr);

        WHEN("Tanks try to move into the same spot")
        {
            tank_1->setMove(moveRight);
            tank_2->setMove(moveLeft);
            gamefield.nextTurn();
            THEN("the first tank dies and the other takes a portion of the damage")
            {
                REQUIRE(gamefield.getActors().size() == 1);
            }
        }

    }
}
