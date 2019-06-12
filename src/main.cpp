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
#include <ui/util.h>
#include <settings/Settings.h>
#include <game/game.h>

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
        printf("Demonstration Mode\n");
        width = 1900;
        height = 1000;
      }else if ((strcmp(argv[counter], "--quiet") == 0 ) && counter + 1 <= argc)
      {
        printf("Quiet Mode\n");
        settings->setQuietMode(true);
      }else if ((strcmp(argv[counter], "--tournament") == 0 ) && counter + 1 <= argc)
      {
        printf("Tournament Mode\n");
        mode = tournament;
      }else if ((strcmp(argv[counter], "--noui") == 0 ) && counter + 1 <= argc)
      {
        printf("No UI Mode\n");
        settings->setUI(false);
      }else if ((strcmp(argv[counter], "--coverage") == 0) && counter + 1 <= argc)
      {
        printf("Coverage Mode\n");
        settings->setCoverageMode(false);
      }else if (((strcmp(argv[counter], "--results") == 0) || strcmp(argv[counter], "-o") == 0) && counter + 2 <= argc)
      {
        printf("Results file set to %s\n", argv[counter+1]);
        settings->setResultsFile(argv[counter+1]);
        counter++;
      }else if((strcmp(argv[counter], "--help") == 0) && counter + 1 <= argc)
      {
        printf("\n\nHelp:\n");
        printf("--demo, -d\n");
        printf("   Demo mode, increases default width to 1900 and height to 1000.\n\n");
        printf("--quiet, -q\n");
        printf("   Quiet text mode, only displays debug text\n\n");
        printf("--tournament, -t\n");
        printf("   Tournament mode, not implemented yet\n\n");
        printf("--noui, -n\n");
        printf("   No UI Mode, hides the UI for faster playback\n\n");
        printf("--coverage, -c\n");
        printf("   Coverage Mode, runs fast settings for coverage testing with graphics\n\n");
        exit(1);
      }else if(argv[counter][0] == '-' && argv[counter][1] != '-'){
        //printf("multi-params\n");
        int i = 1; //start at first argument
        while (argv[counter][i] != '\0'){
            switch (argv[counter][i]){
              case 'd':
                width = 1900;
                height = 1000;
                printf("Demo Mode\n");
                break;
              case 'q':
                settings->setQuietMode(true);
                printf("Quiet Mode\n");
                break;
              case 't':
                mode = tournament;
                printf("Tournament Mode\n");
                break;
              case 'n':
                settings->setUI(false);
                printf("No UI Mode\n");
                break;
              case 'c':
                settings->setCoverageMode(true);
                printf("Coverage Mode\n");
                break;
              case 'h':
                printf("\n\nHelp:\n");
                printf("--demo, -d\n");
                printf("   Demo mode, increases default width to 1900 and height to 1000.\n\n");
                printf("--quiet, -q\n");
                printf("   Quiet text mode, only displays debug text\n\n");
                printf("--tournament, -t\n");
                printf("   Tournament mode, not implemented yet\n\n");
                printf("--noui, -n\n");
                printf("   No UI Mode, hides the UI for faster playback\n\n");
                printf("--coverage, -c\n");
                printf("   Coverage Mode, runs fast settings for coverage testing with graphics\n\n");
                exit(1);
                break;
              default:
                printf("Invalid option specified: %c\n", argv[counter][i]);
                printf("Use --help or -h for command line options.\n");
                exit(1);
                break;
            }
            i++;
          }
      }else{
          printf("Invalid option specified: %s\n", argv[counter]);
          printf("Use --help or -h for command line options.\n");
          exit(1);
      }
      counter++;
    }

    settings->setGameMode(mode);
    //gameMode {none, ai, sp, mp, tournament};
    if (settings->showUI()){
      initOpenGL( argc, argv, width, height, settings );
      glutMainLoop();
    }else{
        Game game;
        game.initGameState(settings);
        game.executeTurn();
    }

    std::cout << "\n GAME OVER \n";
    return 0;
}
