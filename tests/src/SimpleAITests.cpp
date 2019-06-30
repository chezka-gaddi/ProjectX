#include "catch.hpp"
#include <SimpleAI.h>
#include <MapData.h>
#include <PositionData.h>
#include <iostream>

TEST_CASE("SimpleAI constructs")
{
    SimpleAI ai;
    REQUIRE(sizeof(ai) > 0);
}
TEST_CASE("SimpleAI does not attack when no other actors are present")
{
    SimpleAI ai;
    MapData map(1,1); //1x1 map
    PositionData pos(1, 1, 1, 1, 2); //ID of 1, health of 1, position 1,1
    map.tileMap[1][1].actor = new Tile("Tank", 1, 1, 1, 1, nullptr, nullptr); //place tank on the map

    REQUIRE(ai.attack(map, pos) == STAY);
}
TEST_CASE("SimpleAI attacks the nearest actor")
{
    SimpleAI ai;
    MapData map(1,2); //1x2 map
    PositionData pos(1, 1, 1, 1, 2); //ID of 1, health of 1, position 0,0
    map.tileMap[1][1].actor = new Tile("Tank", 1, 1, 1, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][1].actor = new Tile("Tank", 2, 1, 2, 1, nullptr, nullptr); //place tank on the map

    REQUIRE(ai.attack(map, pos) == DOWN);
}
TEST_CASE("SimpleAI moves toward the nearest enemy tank")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 1, 1, 2); //ID of 1, health of 1, position 0,0
    map.tileMap[1][1].actor = new Tile("Tank", 1, 1, 1, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[3][1].actor = new Tile("Tank", 2, 1, 3, 1, nullptr, nullptr); //place tank on the map

    REQUIRE(ai.move(map, pos) == DOWN);
}
TEST_CASE("SimpleAI stays in place if no other tanks are present")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 1, 1, 2); //ID of 1, health of 1, position 1,1
    map.tileMap[1][1].actor = new Tile("Tank", 1, 1, 1, 1, nullptr, nullptr); //place tank on the map

    REQUIRE(ai.move(map, pos) == STAY);
}
TEST_CASE("SimpleAI stays in place if only projectiles are present")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 1, 1, 2); //ID of 1, health of 1, position 1,1
    map.tileMap[1][1].actor = new Tile("Tank", 1, 1, 1, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[3][1].projectile = new Tile("Projectile", -2, 1, 1, 1, nullptr, nullptr); //place tank on the map

    REQUIRE(ai.move(map, pos) == STAY);
}
TEST_CASE("SimpleAI does not crash into other actors")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 1, 1, 2); //ID of 1, health of 1, position 1,1
    map.tileMap[1][1].actor = new Tile("Tank", 1, 1, 1, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][1].actor = new Tile("Tank", -2, 2, 1, 1, nullptr, nullptr); //place tank on the map

    REQUIRE(ai.move(map, pos) == STAY);
}
TEST_CASE("SimpleAI avoids obstacles below")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 1); //ID of 1, health of 1, position 1,0
    map.tileMap[2][1].actor = new Tile("Tank", 1, 2, 2, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][3].actor = new Tile("Tank", 2, 2, 3, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][2].type = "Rock";
    REQUIRE((ai.move(map, pos) == LEFT || ai.move(map,pos) == RIGHT));
}
TEST_CASE("SimpleAI avoids obstacles to the left")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 3, 2); //ID of 1, health of 1, position 2,1
    map.tileMap[2][3].actor = new Tile("Tank", 1, 3, 2, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][1].actor = new Tile("Tank", 2, 1, 2, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][2].type = "Rock";
    REQUIRE((ai.move(map, pos) == UP || ai.move(map,pos) == DOWN));
}
TEST_CASE("SimpleAI avoids obstacles above")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 2, 3); //ID of 1, health of 1, position 1,3
    map.tileMap[3][2].actor = new Tile("Tank", 1, 2, 3, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[1][2].actor = new Tile("Tank", 2, 2, 1, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][2].type = "Rock";
    REQUIRE((ai.move(map, pos) == RIGHT || ai.move(map,pos) == LEFT));
}
TEST_CASE("SimpleAI avoids obstacles to the right")
{
    SimpleAI ai;
    MapData map(3,3); //3x3 map
    PositionData pos(1, 1, 1, 2); //ID of 1, health of 1, position 0, 1
    map.tileMap[2][1].actor = new Tile("Tank", 1, 2, 1, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][3].actor = new Tile("Tank", 2, 2, 3, 1, nullptr, nullptr); //place tank on the map
    map.tileMap[2][2].type = "Rock";
    REQUIRE((ai.move(map, pos) == UP || ai.move(map,pos) == DOWN));
}
