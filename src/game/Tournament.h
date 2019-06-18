/***************************************************************************//**
* @file tournament.h
* @author Jon McKee
* @brief set of function to run a tournament
*******************************************************************************/

#include <settings/Settings.h>
#include <game/game.h>


class Tournament {
public:
    Tournament(Settings * settings, int rounds);
    Tournament();

    void runTournament(); //Runs the entire tournament mode

protected:
    void newGame(); //starts a new game

private:
    Settings * settings;
    Game * game;
    int rounds = 1;
};