#include <game/Tournament.h>

/***************************************************************************//**
 * @author Jon McKee
 * @brief Tournament(Settings, int)
 *
 * Constructor that sets the settings and number of rounds during tournament
 * initialization.
 * 
 * @param[in] s - pointer to the settings to use
 * @param[in] r - The number of rounds to play
 *******************************************************************************/
Tournament::Tournament(std::shared_ptr<Settings> s, int r){
    settings = s;
    rounds = r;
    settings->setUI(false);
    settings->setQuietMode(true);
    newGame();
}
/***************************************************************************//**
 * @author Jon McKee
 * @brief Tournament
 *
 * Empty constructor with default values and a single round
 *******************************************************************************/
Tournament::Tournament(){
    settings = std::shared_ptr<Settings>(new Settings());
    rounds = 1;
    newGame();
}
/***************************************************************************//**
 * @author Jon McKee
 * @brief deconstructor
 *
 * Deconstructor to clean up as we leave
 *******************************************************************************/
Tournament::~Tournament(){
}
/***************************************************************************//**
 * @author Jon McKee
 * @brief newGame
 *
 * Resets relevant settings and creates a new game variable for the next round
 *******************************************************************************/
void Tournament::newGame(){
    game = std::unique_ptr<Game>(new Game());
    game->initGameState(settings);
}
/***************************************************************************//**
 * @author Jon McKee
 * @brief runTournament
 *
 * Entry point to running the tournament.  
 *******************************************************************************/
void Tournament::runTournament(){
    printf("Starting Tournament.\n");
    int roundCounter = 0; //Current round counter
    while (roundCounter < rounds){ //Tournament loop
        roundCounter++; //Increment round counter
        if (roundCounter % (rounds / 10) == 0) //limit output
            printf("Game %d of %d\n",roundCounter, rounds);
        game->executeTurn(); //Run the round
        newGame();
    }
}