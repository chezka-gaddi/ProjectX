////////////////////////////////////////////////////////////////////////////////
// File name: addition_ut.cpp
// Author: Riley Kopp
// Date Updated: 24 Aug 18
// Description: Example UT file
////////////////////////////////////////////////////////////////////////////////

// Includes
#include "catch.hpp"
#include "../../src/addition.h"

////////////////////////////////////////////////////////////////////////////////
// Scenario: Addition Adds two numbers
// Given:   An addition class and two numbers
// When :   The two numbers are passed into addition
// Then :   The returned value is the sum of the two numbers
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Adds Two numbers")
{
   int x = 5;
   int y = 50;

   Addition add;

   REQUIRE(add.two_values(x, y) == 55);
}

////////////////////////////////////////////////////////////////////////////////
// Scenario: Addition Adds two negative numbers
// Given:   An addition class and two negative numbers
// When :   The two numbers are passed into addition
// Then :   The returned value is the sum of the two numbers
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Adds Two Negatives")
{
   int x = -1;
   int y = 5;

   Addition add;

   REQUIRE(add.two_values(x, y) == -6);

}

