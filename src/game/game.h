/***************************************************************************//**
* @file game.h
* @author Chezka Gaddi
* @brief Contains all functions prototypes that maintains Game class.
*******************************************************************************/
#ifndef __GAME_H
#define __GAME_H

//Includes
#include <actors/Actor.h>
#include <actors/ActorInfo.h>
#include <vector>
#include <game/GameField.h>
#include <ui/Drawable.h>
#include <settings/Settings.h>

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

    int executeTurn();
    int executeGame();
    void initGameState(std::shared_ptr<Settings> & setting);
    void initTournState(std::shared_ptr<Settings> & setting, std::shared_ptr<MapData>, std::vector<std::string>, std::vector<std::pair<int, int>>, std::vector<std::string>);

    void closeDown();
    void earlyOut();
    float convertGLXCoordinate( int );
    float convertGLYCoordinate( int );
    void noGUIGame();
    bool checkMaxTurn();

    int getX(){return tankGame->getWidth();};
    int getY(){return tankGame->getHeight();};

    std::vector<ActorInfo> loadPlayers(bool, std::vector<std::pair<int,int>>, std::vector<std::string>, std::vector<Actor*>, attributes, int, int);

    std::vector<std::unique_ptr<Drawable>> objects;       /*!<Holds all of the current actors */
    std::vector<std::unique_ptr<Drawable>> constants;     /*!<Holds the GameFieldDrawable and menus */
    std::vector<std::unique_ptr<Obstacles>> bushes;        /*!<Holds the bushes drawables */
    std::vector<std::unique_ptr<Obstacles>> rocks;         /*!<Holds the rocks drawables */
    std::vector<std::unique_ptr<Obstacles>> trees;         /*!<Holds the trees drawables */
    std::vector<std::unique_ptr<Drawable>> waters;		   /*!<Holds the waters drawables */
    std::vector<std::unique_ptr<Drawable>> specials;       /*!<Holds other special drawables */
    std::vector<std::unique_ptr<Drawable>> sfx;           /*!<Holds the sfx drawables */

private:
    int fieldx;
    int fieldy;
};
#endif //__GAME_H