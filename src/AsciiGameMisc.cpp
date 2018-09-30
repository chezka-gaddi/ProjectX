//
// Created by jlee on 9/24/18.
//

#include <iostream>
#include "AsciiGameMisc.h"
#include "Actor.h"
#include "AsciiTankActor.h"

bool isplayable(std::vector<ActorInfo> actorInfo){
    int sum = 0;
    for(ActorInfo a: actorInfo){

        if(a.id == tankId){
            sum += 1;
        }
    }
    return sum >=2;
}
void displayAscii(GameField gameField, std::vector<ActorInfo> actorInfo){
    std::vector<std::string> asciiGameField();

    for(int i = 0; i <= gameField.getWidth(); i++){
        std::string tempString = "";
        for(int j = 0; j <= gameField.getHeight(); j++){
            tempString += ' ';
        }
        asciiGameField().push_back(tempString.c_str());
    }
    //populate the ascii field (only works on terminals with a constant width typeset)
    for(ActorInfo a: actorInfo){
        if(a.id == tankId){
            asciiGameField()[a.x][a.y] = 'T';
        }
        else{
            asciiGameField()[a.x][a.y] = 'O';
        }
    }
    for(int i = 0; i < 4; i++){
        std::cout << std::endl;
    }
    for(std::string s: asciiGameField()){
         std::cout << s << std::endl;
    }


}

void gameloop(){
    GameField gameField = GameField(10,10);
    //change tankactor here to what ever we have decided to call the ascii tank actor
    AsciiTankActor * player1 = new TankActor();
    AsciiTankActor * player2 = new TankActor();
    //tank actor pointers are made and then packaged into ActorInfo structs
    ActorInfo player1Info = ActorInfo(player1, 1,1,0,0,2);
    ActorInfo player2Info = ActorInfo(player2, 1,1,10,10,2);

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
        //removes all actors with health == 0;
        gameField.cull();
    }
}