//
// Created by jlee on 9/24/18.
//

#include <iostream>
#include "AsciiGameMisc.h"
#include "Actor.h"
#include "AsciiTankActor.h"

bool isplayable(std::vector<ActorInfo> actorInfo){
    int tankCount = 0;
    for (auto a : actorInfo)
    {
        tankCount += (a.id > 0) ? 1 : 0; 
    }
    return (tankCount > 1);
}
void displayAscii(MapData map, std::vector<ActorInfo> actors, int turnCount)
{
    std::cout << map << std::endl;
    std::cout << "Turn: " << turnCount << std::endl;
                     
    for (auto a: actors)
    {
        if (a.id > 0)
        {
            std::cout << "[7m" //Inverted Text Mode
                      << "Player " << a.id
                      << "[0(;31)m " //RED
                      << "Health: " <<  a.health
                      << "[0(;34)m " //BLUE
                      << "Shots: " << a.shots
                      << "[0(;32)m " //GREEN
                      << "Hits: " << a.hits
                      << "[0m"
                      << std::endl;
           
        }
    }
    system("sleep 0.25");
}

void gameloop(){
    
    //change tankactor here to what ever we have decided to call the ascii tank actor
    AsciiTankActor * player1 = new AsciiTankActor();
    AsciiTankActor * player2 = new AsciiTankActor();
    //tank actor pointers are made and then packaged into ActorInfo structs
    ActorInfo player1Info = ActorInfo(player1, 1,1,2,2,1);
    ActorInfo player2Info = ActorInfo(player2, 1,1,18,2,2);
    std::vector<ActorInfo> startActors;
    startActors.push_back(player1Info);
    startActors.push_back(player2Info);
    
    GameField gameField (20,5, startActors, displayAscii);
   
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
