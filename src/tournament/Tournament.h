/***************************************************************************//**
* @file tournament.h
* @author Jon McKee
* @brief set of function to run a tournament
*******************************************************************************/

#include <settings/Settings.h>
#include <game/game.h>
#include <tournament/bracket.h>

class Tournament {
public:
    //constructors
    Tournament(std::shared_ptr<Settings> settings, int rounds);
    Tournament();
    ~Tournament();

    //tournament start
    void runTournament(); //Runs the entire tournament mode

protected:
    //tournament management functions
    void newGame(); //starts a new game

private:
    std::shared_ptr<Settings> settings; //pointer to settings to use
    std::unique_ptr<Game> game;         //pointer to current game
    int rounds = 1;      //number of rounds to play
    std::vector<bracket> bracketList; //Vector containing all the map brackets
    std::vector<player> playerList;
};