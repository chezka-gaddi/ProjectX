#include <tournament/Tournament.h>
#include <algorithm>
#include <utilities/mapLoader.h>
#include <structures/attributes.h>
#include <cstdlib>

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
    int maxRounds, currMatch, count = 1;
    std::vector<std::pair<int,int>> spawnLocations;
    std::shared_ptr<MapData> bMap;
    std::string resultsFile, trackerFile;
    attributes baseAttr;

    //load players
    playerList = parsePlayers();
    //printPlayerInfo();
    //load brackets
    bracketList = parseBrackets();
    //Print bracket information to tournament output folder
    //printBracketInfo();
    //loop through brackets
    system("mkdir -p tResults");
    for (unsigned int b = 0; b < bracketList.size(); b++){
        //calculate max number of rounds
        cBracket = bracketList[b];
        printf("Starting %s bracket.\n", cBracket.mapName.c_str());
        //load spawns
        maxRounds = cBracket.rounds;
        resultsFile = "mkdir -p tResults/bracket" + std::to_string(b);
        system(resultsFile.c_str());
        resultsFile = "tResults/bracket" + std::to_string(b) + "/results.txt";
        for (int r = 0; r < maxRounds; r++){
            currMatch = 1;
            spawnLocations = parseSpawns(cBracket.spawns);
            printf("Round %d of %d.\n", r + 1, maxRounds);
            do{  //loop through iterations
                //Check spawns
                //printSpawnInfo(spawnLocations);
                //load map
                settings->setMapName("../tournament/" + bracketList[b].mapName); //Set map name into settings
                bMap = loadMap(settings);
                //load stats
                baseAttr = parseStats(bracketList[b].stats);
                settings->setAttributes(baseAttr, bMap->width);
                settings->setResultsFile(resultsFile);
                trackerFile = "tResults/bracket" + std::to_string(b) + "/match" + std::to_string(r) + ".txt";
                settings->setTrackingFile(trackerFile);
                settings->setTrackingMode(true);
                //load settings
                parseSettings(bracketList[b].settings, settings);

                //printMatchInfo(spawnLocations, b, currMatch, spawnLocations.size());
                //manual game initialization
                initGame(bMap, bracketList[b].players, spawnLocations);

                //run game
                game->executeGame(); //runs with no images
                count++;
                //store winner/losers


                //delete game
                newGame();

                //continue through iteration
                currMatch++;  //round
            }while(std::next_permutation(spawnLocations.begin(), spawnLocations.end()));
        }
        
        
    }
        
    /*printf("Starting Tournament.\n");
    int roundCounter = 0; //Current round counter
    int limit = rounds / 10;
    while (roundCounter < rounds){ //Tournament loop
        roundCounter++; //Increment round counter
        if (roundCounter % (limit > 0 ? limit : 1) == 0) //limit output
            printf("Game %d of %d\n",roundCounter, rounds);
        game->executeTurn(); //Run the round
        newGame();
    }*/
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

/***************************************************************************//**
 * @author Jon McKee
 * @brief printMatchInfo
 *
 * Outputs the match info to the tournament output folder
 *******************************************************************************/
void Tournament::printMatchInfo(std::vector<std::pair<int,int>> spawnList, int bracket, int cMatch, int tMatch){
    printf("Match %d of %d:\n", cMatch, tMatch);
    for (int i = 0; i < bracketList[bracket].players; i++) {
        printf("%s (%d, %d)\n", playerList[i].name.c_str(), spawnList[i].first, spawnList[i].second);
    }
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief printRoundInfo
 *
 * Outputs the round info to the tournament output folder
 *******************************************************************************/
void Tournament::printRoundInfo(){
    
}

void Tournament::initGame(std::shared_ptr<MapData> map, int players, std::vector<std::pair<int, int>> spawnLocations){
    std::vector<std::string> AINames;
    std::vector<std::string> tankImages;
    std::vector<std::pair<int,int>> tankLocations;

    for (int i = 0; i < players; i++){
        AINames.push_back(playerList[i].name);
        tankImages.push_back(playerList[i].images + "/base.png");
        tankImages.push_back(playerList[i].images + "/turret.png");
        tankImages.push_back(playerList[i].images + "/bullet.png");
        tankLocations.push_back(spawnLocations[i]);
        tankLocations[i].first += map->widthPadding;
        tankLocations[i].second += map->heightPadding;
    }

    game->initTournState(settings, map, AINames, tankLocations, tankImages);
}