#include <tournament/Tournament.h>

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
    //load players
    //load brackets
    bracketList = parseBrackets();
    //Print bracket information to tournament output folder
    printBracketInfo();
    //loop through brackets
        //calculate max number of rounds
        //load map
        //load spawns
        //loop through iterations
            //manual game initialization
            //run game
            //store winner/losers
            //delete game
            //continue through iteration




    printf("Starting Tournament.\n");
    int roundCounter = 0; //Current round counter
    int limit = rounds / 10;
    printf("Limit: %d\n", limit);
    while (roundCounter < rounds){ //Tournament loop
        roundCounter++; //Increment round counter
        if (roundCounter % (limit > 0 ? limit : 1) == 0) //limit output
            printf("Game %d of %d\n",roundCounter, rounds);
        game->executeTurn(); //Run the round
        newGame();
    }
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief printBracketInfo
 *
 * Outputs the bracketInfo to the tournament output folder
 *******************************************************************************/
void Tournament::printBracketInfo(){
    printf("Bracket information:\n");
    for (auto& b : bracketList) {
        printf("Map Name:");
        printf(" %s\n", b.mapName.c_str());
        printf("Stats Set Used:");
        printf(" %s\n", b.stats.c_str());
        printf("Image Set Used:");
        printf(" %s\n", b.images.c_str());
        printf("Settings Set Used:");
        printf(" %s\n", b.settings.c_str());
        printf("Number of players:");
        printf(" %d\n", b.players);
        printf("\n");
    }
}