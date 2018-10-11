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
Game::Game() : turn(0) {}

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
    turn++;
    std::cout << "Game Turn [" << turn << "] executed\n";
    std::cout << "Repainting game objects\n";
    glutPostRedisplay();
}

void Game::initGameState()
{
    std::cout << "Game::Loading playfield\n";
    std::cout << "Game::Loading tanks\n";

    // Build Drawables
    Drawable * temp = new TankDrawable(1, 1.0f, .5f);
    std::vector<ActorInfo> actors;
    ActorInfo player_1(
            new AsciiTankActor()
          , 100
          , 100
          , 2
          , 5
          , 1
          , 1
          , temp);

    temp = new TankDrawable(2, -1, .5);
    ActorInfo player_2(
            new AsciiTankActor()
          , 100
          , 100
          , 13
          , 5
          , 1
          , 1
          , temp);

    actors.push_back(player_1);
    actors.push_back(player_2);


    // Create the Gamefield
    GameField game (15, 9, actors);



    std::cout << "Game::Setting turn counter\n";

    turn = 0;
}

void Game::closeDown()
{
    std::cout << "Game::Closing game, cleaning up memory\n";
    std::cout << "Game::Writing results file\n";
}
