#include "catch.hpp"
#include "../../src/AsciiTankActor.h"

using namespace std;

TEST_CASE("Call move function to create and return MoveData struct")
{
   AsciiTankActor tank;
   tank.move( 1, 9);
}
