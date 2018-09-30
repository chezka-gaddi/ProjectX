////////////////////////////////////////////////////////////////////////////////
// File Name: main.cpp
// Author: Riley Kopp
// Date Modified: 25 Aug 18
// Description: The main function for the platform
////////////////////////////////////////////////////////////////////////////////



// Includes
#include <iostream>
#include "AsciiGameMisc.h"
#include "AsciiTankActor.h"






// Main

int main(void)
{

   //this is the start up of the game logic atleast 2 tanks need to be on the field at any given time
   gameloop();
   std::cout << "\n\n\n\n\n game over \n\n\n\n\n\n";
   return 0;
}
