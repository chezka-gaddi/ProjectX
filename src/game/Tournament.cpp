#include <game/Tournament.h>

Tournament::Tournament(Settings * s, int r){
    settings = s;
    rounds = r;
    settings->setUI(false);
    settings->setQuietMode(true);
    newGame();
}

Tournament::Tournament(){
    settings = new Settings();
    rounds = 1;
    newGame();
}

void Tournament::newGame(){
    game = new Game();
    settings->setTurn(0);
    settings->setActTurn(0);
    settings->setModCounter(0);
    game->initGameState(settings);
}

void Tournament::runTournament(){
    printf("Starting Tournament.");
    int turnCounter = 0;
    while (turnCounter < rounds){
        turnCounter++;
        printf("Game %d of %d\n",turnCounter, rounds);
        game->executeTurn();
        delete game;
        newGame();
    }
}