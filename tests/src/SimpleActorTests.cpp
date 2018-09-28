#include "catch.hpp"
#include <SimpleActor.h>
#include <Actor.h>


TEST_CASE("SimpleActor constructs correctly")
{
    SimpleActor a;
    REQUIRE(sizeof(a) > 0);
}
TEST_CASE("SimpleActor.move() returns up")
{
    SimpleActor a;
    MapData m;
    PositionData p;
    REQUIRE(a.move(m,p) == up);
}
TEST_CASE("SimpleActor.attack() attacks 0,0")
{
    SimpleActor a;
    MapData m;
    PositionData p;
    AttackData result;
    result = a.attack(m,p);
    REQUIRE(( result.attack_x == 0 && result.attack_y == 0));
}
