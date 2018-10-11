#include "catch.hpp"
#include <SimpleAI.h>
#include <MapData.h>
#include <PositionData.h>
#include <AttackData.h>
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
    PositionData pos(1, 1, 0, 0); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place tank on the map
    
    REQUIRE(ai.attack(map, pos).damage == 0);
}
TEST_CASE("SimpleAI attacks the nearest actor")
{
    SimpleAI ai;
    MapData map(1,2); //1x2 map
    PositionData pos(1, 1, 0, 0); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[1] = 2; //place enemy tank on map
    
    REQUIRE(ai.attack(map, pos) == AttackData(0,1,1));
}
TEST_CASE("SimpleAI moves toward the nearest enemy tank")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[2] = 2; //place enemy tank on map
    
    REQUIRE(ai.move(map, pos) == down);
}
TEST_CASE("SimpleAI stays in place if no other tanks are present")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    
    REQUIRE(ai.move(map, pos) == stay);
}
TEST_CASE("SimpleAI stays in place if only projectiles are present")
{
    SimpleAI ai;
    MapData map(1,3); //1x3 map
    PositionData pos(1, 1, 0, 0); //ID of 1, health of 1, position 0,0
    map.map[0] = 1; //place AI on the map
    map.map[2] = -2; //enemy projectile
    
    REQUIRE(ai.move(map, pos) == stay);
}
