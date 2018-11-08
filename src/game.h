/***************************************************************************//**
* @file game.h
* @author Chezka Gaddi
* @brief Contains all functions prototypes that maintains Game class.
*******************************************************************************/
#ifndef __GAME_H
#define __GAME_H

//Includes
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "ActorInfo.h"
#include "GameField.h"
#include "Drawable.h"
#include "Actor.h"
#include "SimpleAI.h"
#include "DynamicLoader.h"
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;


/*!<Enum class for the gameMode */
enum gameMode {ai, sp, mp};


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Class
*
* Game is an interface for the GameField class and openGl application
*******************************************************************************/
class Game
{
public:
    GameField *tankGame;               /*!<Pointer to the game manager */
    gameMode g_mode;                   /*!<Type of game to be ran */
    int turn;

    Game();
    Game(gameMode mode);
    ~Game();

    void makeDrawables();
    void executeTurn();
    void initGameState();
    void closeDown();
    void earlyOut();
    float convertGLXCoordinate( int );
    float convertGLYCoordinate( int );

    int getX(){return fieldx;};
    int getY(){return fieldy;};

    int getAISpeed(){return idle_speed;};
    
    vector <Drawable *> objects;       /*!<Holds all of the current actors */
    vector <Drawable *> constants;     /*!<Holds the GameFieldDrawable and menus */
    vector <Drawable *> bushes;        /*!<Holds the bushes drawables */
    vector <Drawable *> rocks;         /*!<Holds the rocks drawables */
    vector <Drawable *> trees;         /*!<Holds the trees drawables */
    vector <Drawable *> specials;       /*!<Holds other special drawables */
    vector <Drawable *> sfx;           /*!<Holds the sfx drawables */

private:
    int fieldx;
    int fieldy;
    int idle_speed;
};

#endif //__GAME_H
