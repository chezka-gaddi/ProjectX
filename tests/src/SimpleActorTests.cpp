#include "catch.hpp"
#include <SimpleActor.h>
#include <Actor-Alternate.h>

TEST_CASE("SimpleActor constructs correctly")
{
    SimpleActor a;
    REQUIRE(sizeof(a) > 0);
}
