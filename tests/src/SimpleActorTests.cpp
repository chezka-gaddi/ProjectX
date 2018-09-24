#include "catch.hpp"
#include <SimpleActor.h>
#include <Actor-Alternate.h>


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
