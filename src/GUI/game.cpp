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
    TankDrawable tank1( 1, -1.0f, -1.3f );
    TankDrawable tank2( 2, 1.0f, 0.5f );
    tanks.push_back( tank1 );
    tanks.push_back( tank2 );
    std::cout << "Game::Setting turn counter\n";
    turn = 0;
}

void Game::closeDown()
{
    std::cout << "Game::Closing game, cleaning up memory\n";
    std::cout << "Game::Writing results file\n";
}
