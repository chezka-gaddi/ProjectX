//
// Created by jlee on 9/24/18.
//

#include <iostream>
#include "AsciiGameMisc.h"
#include "Actor.h"
#include "AsciiTankActor.h"

bool isplayable(std::vector<ActorInfo> actorInfo){
    
    return actorInfo.size() > 1;
}
void displayAscii(MapData map){
    std::cout << map;
    system("sleep 0.25");
}

void gameloop(){
    
    //change tankactor here to what ever we have decided to call the ascii tank actor
    AsciiTankActor * player1 = new AsciiTankActor(true);
    AsciiTankActor * player2 = new AsciiTankActor(true);
    //tank actor pointers are made and then packaged into ActorInfo structs
    ActorInfo player1Info = ActorInfo(player1, 1,1,1,1,1);
    ActorInfo player2Info = ActorInfo(player2, 1,1,8,8,2);
    std::vector<ActorInfo> startActors;
    startActors.push_back(player1Info);
    startActors.push_back(player2Info);
    
    GameField gameField (10,10, startActors, displayAscii);
   
    //the is the main game loop
    while(isplayable(gameField.getActors())){
        //displays the current game state
        displayAscii(gameField.getMapData());
        std::vector<ActorInfo> actors = gameField.getActors();
        //makes the next moves
        gameField.nextTurn();
    }
    //Final Field State
    displayAscii(gameField.getMapData());
}
