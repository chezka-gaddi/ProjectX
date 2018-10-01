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
void displayAscii(GameField gameField, std::vector<ActorInfo> actorInfo){
    std::cout << gameField.getMapData(); //display the map


}

void gameloop(){
    GameField gameField = GameField(10,10);
    //change tankactor here to what ever we have decided to call the ascii tank actor
    AsciiTankActor * player1 = new AsciiTankActor();
    AsciiTankActor * player2 = new AsciiTankActor();
    //tank actor pointers are made and then packaged into ActorInfo structs
    ActorInfo player1Info = ActorInfo(player1, 1,1,1,1,1);
    ActorInfo player2Info = ActorInfo(player2, 1,1,8,8,2);

    //adding the TankActors to the game field
    gameField.addActor(player1Info);
    gameField.addActor(player2Info);

   
    //the is the main game loop
    while(isplayable(gameField.getActors())){
        //displays the current game state
        std::vector<ActorInfo> actors = gameField.getActors();
        displayAscii(gameField, actors);
        //makes the next moves
        gameField.nextTurn();
    }
}
