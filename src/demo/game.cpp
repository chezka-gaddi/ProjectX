#include "game.h"

/***************************************************************************//**
* @brief Constructor
*
* Here's where you handle things that should happen during a turn
* - Ask each of the tanks for their action
* - Update the game state
* - Issue a call to repaint the playfield, projectiles, tanks, etc.
*
*
*******************************************************************************/
Game::Game() : turn(0)
{
    // Build Drawables
    std::vector<ActorInfo> actors;
    ActorInfo player_1(
            new AsciiTankActor()
          , 100
          , 100
          , 2
          , 5
          , 1
          , 1);

    ActorInfo player_2(
            new AsciiTankActor()
          , 100
          , 100
          , 13
          , 5
          , 2
          , 1);

    actors.push_back(player_1);
    actors.push_back(player_2);


    // Create the Gamefield
    game_m  = new GameField(15, 9, actors);
}

/***************************************************************************//**
* @brief executeTurn
*
* Here's where you handle things that should happen during a turn
* - Ask each of the tanks for their action
* - Update the game state
* - Issue a call to repaint the playfield, projectiles, tanks, etc.
*
*******************************************************************************/
void Game::executeTurn()
{
    Drawable * temp_draw = nullptr;
    MapData map;
    turn++;
    std::cout << "Game Turn [" << turn << "] executed\n";
    std::cout << "Repainting game objects\n";
    map = game_m->getMapData();
    for(int index = 0; index < map.map.size(); index++)
    {
       if(map.map.at(index) > 0)
       {
          // Calculate floating point pos
          temp_draw = new TankDrawable(map.map.at(index), 1, .5);
          objects.push_back(temp_draw);

       }

       else if(map.map.at(index) < 0)
       {
          // Calculate floating point pos
          temp_draw = new Projectile(map.map.at(index), 1, .5);
          objects.push_back(temp_draw);

       }
    }
    for(int index = 0; index < map.obstacleMap.size(); index++)
    {
       if(map.obstacleMap.at(index) != false)
       {
          // Calculate floating point pos
          temp_draw = new Obstacles( 1, .5);
          objects.push_back(temp_draw);

       }

    }

    temp_draw = new GameFieldDrawable();
    objects.push_back(temp_draw);

    glutPostRedisplay();
    for (auto index : objects)
    {
      delete index;
    }
    game_m->nextTurn();

}

static bool isplayable(std::vector<ActorInfo> actorInfo){
    int tankCount = 0;
    for (auto a : actorInfo)
    {
        tankCount += (a.id > 0) ? 1 : 0;
    }
    return (tankCount > 1);
}

void Game::initGameState()
{
    std::cout << "Game::Loading playfield\n";
    std::cout << "Game::Loading tanks\n";



    while(isplayable(game_m->getActors()))
    {
      executeTurn();

    }

    std::cout << "Game::Setting turn counter\n";

    turn = 0;
}

void Game::closeDown()
{
    std::cout << "Game::Closing game, cleaning up memory\n";
    std::cout << "Game::Writing results file\n";
}
