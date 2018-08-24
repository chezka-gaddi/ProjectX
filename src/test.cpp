////////////////////////////////////////////////////////////////////////////////
/// File: test.cpp
/// Author: Riley Kopp
/// Date Updated: 23 Aug 2018
/// Description: The test file to test the UT environment
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "addition.h"

int main(void)
{
   int x = 100;
   int y = 10;
   int sum;

   Addition add;

   sum = add.two_values(x, y);

   std::cout << "The sum is: " << sum << std::endl;
   return 0;
}
