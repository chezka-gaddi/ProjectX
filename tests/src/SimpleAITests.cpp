#include "catch.hpp"
#include <SimpleAI.h>
#include <MapData.h>
#include <PositionData.h>
#include <AttackData.h>


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

