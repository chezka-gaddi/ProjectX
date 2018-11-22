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
#include <memory>

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
    int turn = 0;
    int actTurn = 0; //0 causes issues on first display call
    int modCounter = 7;
    bool ui = true;

    Game();
    Game(gameMode mode);
    ~Game();

    void makeDrawables();
    void executeTurn();
    void initGameState();
    void closeDown();
    void earlyOut();
    void createConfig();
    float convertGLXCoordinate( int );
    float convertGLYCoordinate( int );

    int getX(){return fieldx;};
    int getY(){return fieldy;};

    int getAISpeed(){return idle_speed;};
    
    vector <std::unique_ptr<Drawable>> objects;       /*!<Holds all of the current actors */
    vector <Drawable *> constants;     /*!<Holds the GameFieldDrawable and menus */
    vector <Obstacles *> bushes;        /*!<Holds the bushes drawables */
    vector <Obstacles *> rocks;         /*!<Holds the rocks drawables */
    vector <Obstacles *> trees;         /*!<Holds the trees drawables */
    vector <Drawable *> waters;		   /*!<Holds the waters drawables */
    vector <Drawable *> specials;       /*!<Holds other special drawables */
    vector <std::unique_ptr<Drawable>> sfx;           /*!<Holds the sfx drawables */
    

private:
    int fieldx;
    int fieldy;
    int idle_speed;
    int max_turns = 200;
    int activeId;
};

#endif //__GAME_H
