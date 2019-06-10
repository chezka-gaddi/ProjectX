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
 * @verbatim
https://gitlab.mcs.sdsmt.edu/7472586/Slackers_Platform
 @endverbatim
 ******************************************************************************/



// Includes
#include <iostream>
#include <memory>
#include <stdio.h>
#include <util.h>
#include <Settings.h>
#include <game.h>

// Main

int main(int argc, char **argv)
{
    Settings * settings = new Settings;
    gameMode mode = settings->getGameMode();
    
    //game display height
    int height = 727, width = 1000;
    //agument counter
    int counter = 1;    

    //printf("%d\n", argc);
    //printf("%s\n", argv[argc-1]);

    //this is the start up of the game logic atleast 2 tanks need to be on the field at any given time
    while(counter < argc)
    {
      if ((strcmp(argv[counter], "--demo")==0)  && counter + 1 <= argc)
      {
        printf("demo mode\n");
        width = 1900;
        height = 1000;
      }else if ((strcmp(argv[counter], "--quiet") == 0 ) && counter + 1 <= argc)
      {
        printf("quiet mode\n");
        mode = quiet;
      }else if ((strcmp(argv[counter], "--tournament") == 0 ) && counter + 1 <= argc)
      {
        printf("tournament mode\n");
        mode = tournament;
      }else if ((strcmp(argv[counter], "--noui") == 0 ) && counter + 1 <= argc)
      {
        printf("no ui mode\n");
        mode = noui;
      }else if ((strcmp(argv[counter], "--coverage") == 0) && counter + 1 <= argc)
      {
        printf("coverage mode\n");
        settings->setCoverageMode();
      }else if(argv[counter][0] == '-' && argv[counter][1] != '-'){
        //printf("multi-params\n");
        int i = 1; //start at first argument
        while (argv[counter][i] != '\0'){
            switch (argv[counter][i]){
              case 'd':
                width = 1900;
                height = 1000;
                printf("demo mode\n");
                break;
              case 'q':
                mode = quiet;
                printf("quiet mode\n");
                break;
              case 't':
                mode = tournament;
                printf("tournament mode\n");
                break;
                case 'n':
                mode = noui;
                printf("no ui mode\n");
                break;
              case 'c':
                settings->setCoverageMode();
                printf("multi-params\n");
                break;
              default:
                printf("Invalid option specified: %c\n", argv[counter][i]);
                exit(1);
                break;
            }
            i++;
          }
      }else{
          printf("Invalid option specified: %s\n", argv[counter]);
          exit(1);
      }
      counter++;
    }

    settings->setGameMode(mode);
    //gameMode {none, ai, sp, mp, quiet, coverage};
    if (mode == ai || mode == sp || mode == mp || mode == quiet){
      initOpenGL( argc, argv, width, height, settings );
      glutMainLoop();
    }else{
        Game game;
        settings->setUI(false);
        game.initGameState(settings);
        game.executeTurn();
    }

    std::cout << "\n GAME OVER \n";
    return 0;
}
