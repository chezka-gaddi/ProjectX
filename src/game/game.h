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
#include <actors/ActorInfo.h>
#include <game/GameField.h>
#include <ui/Drawable.h>
#include <actors/Actor.h>
#include <tanks/SimpleAI.h>
#include <utilities/tankLoader.h>
#include <utilities/mapLoader.h>
#include <settings/Settings.h>
#include <game/gameover.h>
#include <game/configParser.h>
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
    std::unique_ptr<GameField> tankGame;               /*!<Pointer to the game manager */
    std::shared_ptr<Settings> settings;                /*!<Pointer to the settings holder*/
    Game();
    Game(gameMode mode);
    ~Game();

    void executeTurn();
    void initGameState(std::shared_ptr<Settings> setting);
    void closeDown();
    void earlyOut();
    float convertGLXCoordinate( int );
    float convertGLYCoordinate( int );
    void noGUIGame();
    bool checkMaxTurn();

    int getX(){return tankGame->getWidth();};
    int getY(){return tankGame->getHeight();};

    std::vector<ActorInfo> loadPlayers(bool, std::vector<std::pair<int,int>>, std::vector<std::string>, std::vector<Actor*>, attributes, int, int);

    vector<std::unique_ptr<Drawable>> objects;       /*!<Holds all of the current actors */
    vector<std::unique_ptr<Drawable>> constants;     /*!<Holds the GameFieldDrawable and menus */
    vector<std::unique_ptr<Obstacles>> bushes;        /*!<Holds the bushes drawables */
    vector<std::unique_ptr<Obstacles>> rocks;         /*!<Holds the rocks drawables */
    vector<std::unique_ptr<Obstacles>> trees;         /*!<Holds the trees drawables */
    vector<std::unique_ptr<Drawable>> waters;		   /*!<Holds the waters drawables */
    vector<std::unique_ptr<Drawable>> specials;       /*!<Holds other special drawables */
    vector<std::unique_ptr<Drawable>> sfx;           /*!<Holds the sfx drawables */

private:
    int fieldx;
    int fieldy;
};
#endif //__GAME_H