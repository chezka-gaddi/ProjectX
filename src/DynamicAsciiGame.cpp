//
// Created by jlee on 10/12/18.
//

#include "DynamicAsciiGame.h"
#include "DynamicLoader.h"

void DL_gameloop(){

    std::vector<ActorInfo> startActors;

    int x = 20;
    int y = 5;
    int i = 0;

    for(auto a: *TankMakers()){

        void* p = a.second;
        Actor * actor = static_cast<Actor*> (p);
        startActors.push_back(ActorInfo(actor,1,2,rand() % x, rand()% y,2,i));
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
