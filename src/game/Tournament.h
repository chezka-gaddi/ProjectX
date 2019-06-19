/***************************************************************************//**
* @file tournament.h
* @author Jon McKee
* @brief set of function to run a tournament
*******************************************************************************/

#include <settings/Settings.h>
#include <game/game.h>


class Tournament {
public:
    //constructors
    Tournament(Settings * settings, int rounds);
    Tournament();
    ~Tournament();

    //tournament start
    void runTournament(); //Runs the entire tournament mode

protected:
    //tournament management functions
    void newGame(); //starts a new game

private:
    Settings * settings; //pointer to settings to use
    Game * game;         //pointer to current game
    int rounds = 1;      //number of rounds to play
};