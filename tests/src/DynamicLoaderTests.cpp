#include "catch.hpp"
#include <DynamicLoader.h>
#include <vector>
#include <string>
#include <Actor.h>



TEST_CASE("DynamicTankLoader returns a vector of Actor *")
{
    std::vector<Actor *> actors = dynamicTankLoader(std::vector<std::string>(0));
    REQUIRE(actors.size() == 0);
}

TEST_CASE("DynamicTankLoader can load a tank")
{
    std::vector<std::string> actNames = {"SimpleAI"};
    std::vector<Actor *> actors = dynamicTankLoader(actNames);
    REQUIRE(actors.size() == 1);
}
