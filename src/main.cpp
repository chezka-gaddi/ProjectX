////////////////////////////////////////////////////////////////////////////////
// File Name: main.cpp
// Author: Riley Kopp
// Date Modified: 25 Aug 18
// Description: The main function for the platform
////////////////////////////////////////////////////////////////////////////////



// Includes
#include <iostream>
#include "AsciiGameMisc.h"
#include "AsciiTankActor.h"






// Main

int main(void)
{

   //this is the start up of the game logic atleast 2 tanks need to be on the field at any given time
   GameField gameField = GameField(10,10);
   //change tankactor here to what ever we have decided to call the ascii tank actor
   AsciiTankActor * player1 = new TankActor();
   AsciiTankActor * player2 = new TankActor();
   //tank actor pointers are made and then packaged into ActorInfo structs
   ActorInfo player1Info = ActorInfo();
   ActorInfo player2Info = ActorInfo();
   //assigning data values to the actor info made it verbose to tell what exactly is happening
   player1Info.act_p = player1;
   player2Info.act_p = player2;

   player1Info.health = 1;
   player2Info.health = 1;
   player1Info.damage = 1;
   player2Info.damage = 1;

   player1Info.x = 0;
   player1Info.y = 0;

   player2Info.x = 10;
   player2Info.y = 10;

   player1Info.id = 2;
   player2Info.id = 2;
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

   std::cout << "\n\n\n\n\n game over \n\n\n\n\n\n";
   return 0;
}
