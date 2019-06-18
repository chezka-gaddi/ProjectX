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

    void runTournament();

protected:
    void newGame();

private:
    Settings * settings;
    Game * game;
    int rounds = 1;
};