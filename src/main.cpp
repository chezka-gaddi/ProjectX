/***************************************************************************//**
 * @file main.cpp
 *
 * @mainpage 'Capture the Flag' Tank Game
 *
 * @brief Main function for Capture the Flag
 *
 * @section Course Information
 *
 * @date Sept. 30 2018
 *
 * @par Professor: Dr Hinker
 *
 * @section Program Description
 *
 * @par Description
 *    'Capture the Flag' Tank game is built entirely with C++ using the GLUT
 *    libraries for graphics.
 *
 *    The Game is 'Battle Royale' style where AI tanks will fight until one tank
 *    remains. To create tanks for the game, users must provide a Dynamically
 *    Linked Library that inherits from the Actor class. 
 *
 * @section Compile Section
 *
 * @par Build
 * @verbatim
 % make
 @endverbatim
 * @par Run
 * @verbatim
 % ./platform
@endverbatim
 *
 * @par Usage
 * 
 *
 * @section To Do,  Bugs, and Mods
 *
 *
 * @par Revision History
 * 2018-10-13 Changed main to use dynamic linking
 * @verbatim
https://gitlab.mcs.sdsmt.edu/7472586/Slackers_Platform
 @endverbatim
 ******************************************************************************/



// Includes
#include <iostream>
#include "AsciiGameMisc.h"
#include "AsciiTankActor.h"
#include "DynamicLoader.h"
#include "Actor.h"

#include <vector>
#include <string>




// Main

int main(int argc, char **argv) //command line arguments are the tanks to load.
{
    std::vector<std::string> tanks (argc - 1);

    for (int i = 1; i < argc; ++i)
    {
        //get the tank names from the CLI
        tanks[i - 1] = argv[i];
    }

    //get the actor pointers from the loader
    std::vector<Actor *> actors = dynamicTankLoader(tanks);

    //if there aren't 2 actors, there is no game to play.
    if(actors.size() < 2)
        return -1;
    
    //this is the start up of the game logic atleast 2 tanks need to be on the field at any given time
    gameloop(actors);
    std::cout << "\n\n\n\n\n game over \n\n\n\n\n\n";
    return 0;
}
