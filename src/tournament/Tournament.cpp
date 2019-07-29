#include <tournament/Tournament.h>
#include <algorithm>

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
    bracket cBracket;
    int maxRounds;
    std::vector<std::pair<int,int>> spawnLocations;

    //load players
    playerList = parsePlayers();
    printPlayerInfo();
    //load brackets
    bracketList = parseBrackets();
    //Print bracket information to tournament output folder
    printBracketInfo();
    //loop through brackets
    for (unsigned int b = 0; b < bracketList.size(); b++){
        //calculate max number of rounds
        cBracket = bracketList[b];
        printf("Starting %s bracket.\n", cBracket.mapName.c_str());
        spawnLocations = parseSpawns(cBracket.spawns);
        //printSpawnInfo(spawnLocations);
        do{
            printSpawnInfo(spawnLocations);
        }while(std::next_permutation(spawnLocations.begin(), spawnLocations.end()));
        //load map
        //load spawns
        //loop through iterations
            //manual game initialization
            //run game
            //store winner/losers
            //delete game
            //continue through iteration
    }
        




    printf("Starting Tournament.\n");
    int roundCounter = 0; //Current round counter
    int limit = rounds / 10;
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
        printf("Map Name: %s\n", b.mapName.c_str());
        printf("Stats Set Used: %s\n", b.stats.c_str());
        printf("Image Set Used: %s\n", b.images.c_str());
        printf("Settings Set Used: %s\n", b.settings.c_str());
        printf("Spawns Set Used: %s\n", b.spawns.c_str());
        printf("Number of players: %d\n\n", b.players);
    }
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief printPlayerInfo
 *
 * Outputs the player info to the tournament output folder
 *******************************************************************************/
void Tournament::printPlayerInfo(){
    printf("Player information:\n");
    for (auto& p : playerList) {
        printf("Player Name: %s (%s)\n", p.name.c_str(), p.images.c_str());
        printf("Wins: %d\n", p.wins);
        printf("Losses: %d\n", p.losses);
        printf("Draw: %d\n", p.participated - p.wins - p.losses);
        printf("Participated: %d\n\n", p.participated);
    }
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief printSpawnInfo
 *
 * Outputs the spawn info to the tournament output folder
 *******************************************************************************/
void Tournament::printSpawnInfo(std::vector<std::pair<int,int>> spawnList){
    printf("Available Spawns:  ");
    for (auto& s : spawnList) {
        printf("(%d, %d), ", s.first, s.second);
    }
    printf("\n");
}