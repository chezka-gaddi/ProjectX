//
// Created by jlee on 9/24/18.
//

#include <iostream>
#include "AsciiGameMisc.h"
#include "Actor.h"
#include "SimpleAI.h"
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
    system("sleep 0.3");
}

void gameloop(std::vector<Actor *> actors){

    std::vector<ActorInfo> startActors;

    int x = 20;
    int y = 5;
    int i = 1;

    //generate a start postion and ActorInfo for all actors in the game
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
