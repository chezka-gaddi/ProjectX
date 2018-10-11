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
    
    Drawable *tank1 = new TankDrawable( 1, -1.0f, -1.3f );
    Drawable *tank2 = new TankDrawable( 2, 1.0f, 0.5f );
    Drawable *menu = new Menu();
    Drawable *field = new GameField();
    Drawable *tree = new Obstacles( 1, -0.5f, -1.0f );
    Drawable *rock = new Obstacles( 2, 0.8f, 0.2f );
    
    objects.push_back( menu );
    objects.push_back( field );
    objects.push_back( tank1 );
    objects.push_back( tank2 );
    objects.push_back( tree );
    objects.push_back( rock );
    
    std::cout << "Game::Setting turn counter\n";
    
    turn = 0;
}

void Game::closeDown()
{
    std::cout << "Game::Closing game, cleaning up memory\n";
    std::cout << "Game::Writing results file\n";
}
