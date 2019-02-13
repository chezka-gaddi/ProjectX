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
#include "Settings.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>

using namespace std;


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
    Settings *settings;                /*!<Pointer to settings */
    Game();
    Game(gameMode mode);
    ~Game();

    void makeDrawables();
    void executeTurn();
    void initGameState(Settings setting);
    void closeDown();
    void earlyOut();
    void createConfig();
    float convertGLXCoordinate( int );
    float convertGLYCoordinate( int );
    void gameOver(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner);

    int getX(){return fieldx;};
    int getY(){return fieldy;};

    void loadPlayers(bool, std::vector<ActorInfo>, std::vector<std::pair<int,int>>, std::vector<std::string>, std::vector<Actor*>, attributes, int, int);
    
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
    int activeId;
};

#endif //__GAME_H
