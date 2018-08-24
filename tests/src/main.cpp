////////////////////////////////////////////////////////////////////////////////
/// File: main.cpp
/// Author: Riley Kopp
/// Updated: 23 Aug 18
/// Description: The main function for the Unit tests
////////////////////////////////////////////////////////////////////////////////



// Includes
#include <limits.h>
#include "gtest/gtest.h"


// Main for UTs
int main(int argc, char ** argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
