////////////////////////////////////////////////////////////////////////////////
// File Name: main.cpp
// Author: Riley Kopp
// Date Modified: 25 Aug 18
// Description: The main function for the platform
////////////////////////////////////////////////////////////////////////////////



// Includes
#include <iostream>
#include "AsciiGameMisc.h"
#include "TankActor.h"






// Main

int main(void)
{
   GameField gameField = GameField(10,10);
   //change tankactor here to what ever we have decided to call the ascii tank actor
   TankActor * player1 = new TankActor();
   TankActor * player2 = new TankActor();

   ActorInfo player1Info = ActorInfo();
   ActorInfo player2Info = ActorInfo();

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

   gameField.addActor(player1Info);
   gameField.addActor(player2Info);


   while(isplayable(gameField.getActors())){

      std::vector<ActorInfo> actors = gameField.getActors();
      displayAscii(gameField, actors);

      gameField.nextTurn();

      gameField.cull();
   }

   std::cout << "\n\n\n\n\n game over \n\n\n\n\n\n";
   return 0;
}
