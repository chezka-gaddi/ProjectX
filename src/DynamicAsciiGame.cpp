//
// Created by jlee on 10/12/18.
//

#include "DynamicAsciiGame.h"
#include "DynamicLoader.h"

void DL_gameloop(std::vector<Actor *> actors){

    std::vector<ActorInfo> startActors;

    int x = 20;
    int y = 5;
    int i = 1;

   
    for(auto a:  actors)
    {

        startActors.push_back(ActorInfo(a,1,2,rand() % x, rand()% y,i));
        i++;
    }
    
    GameField gameField (x,y, startActors, displayAscii);

    //the is the main game loop
    while(isplayable(gameField.getActors())){
        //displays the current game state
        displayAscii(gameField.getMapData(), gameField.getActors(), gameField.getTurnCount());
        std::vector<ActorInfo> actors = gameField.getActors();
        //makes the next moves
        gameField.nextTurn();
    }

    //Final Field State
    displayAscii(gameField.getMapData(), gameField.getActors(), gameField.getTurnCount());
}
