#include "catch.hpp"
#include "../../src/addition.h"

TEST_CASE("Adds Two numbers")
{
   int x = 5;
   int y = 50;

   Addition add;

   REQUIRE(add.two_values(x, y) == 55);
}

TEST_CASE("Adds Two Negatives")
{
   int x = -1;
   int y = -5;

   Addition add;

   REQUIRE(add.two_values(x, y) == -6);

}

