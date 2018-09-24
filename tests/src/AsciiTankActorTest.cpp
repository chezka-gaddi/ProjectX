#include "catch.hpp"
#include <../../src/AsciiTankActor.h>

using namespace std;

TEST_CASE("Create an AsciiTankActor object.")
{
   AsciiTankActor tank;
   REQUIRE( sizeof(tank) > 0 ); 
}
