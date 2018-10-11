#include "catch.hpp"
#include <SimpleAI.h>

TEST_CASE("SimpleAI constructs")
{
    SimpleAI ai;
    REQUIRE(sizeof(ai) > 0);
}
