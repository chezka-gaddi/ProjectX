/**
 * @file GameField.h
 * @author David Donahue
 * @brief GameField manages the play field and  actors.
 */

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <vector>
#include <algorithm>
#include <actors/ProjectileActor.h>
#include <structures/PositionData.h>
#include <actors/Actor.h>
#include <map/MapData.h>
#include <actors/ActorInfo.h>
#include <structures/direction.h>
#include <settings/Settings.h>
#include <iostream>
#include <ctime>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <utilities/gameTracker.h>

/***************************************************************************//**
* @class GameField
* @author David Donahue
* @par Description
* The class that will act as the manager of the gamefield
* *****************************************************************************/

class Game;
class Settings;

class GameField
{
public:
    /**********************************************/
    /********constructors/deconstructors***********/
    /**********************************************/
    GameField(int width = 10, int height = 10);
    GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(Settings *), Game *, Settings *);
    ~GameField();
    /*******************************/
    /*************getters***********/
    /*******************************/
    int getWidth();
    int getHeight();
    std::vector<ActorInfo> getActors();
    std::vector<ActorInfo> * getActorsPointer();
    const std::vector<ActorInfo> &getActorsConst();
    std::vector<std::pair<int,int>> * getSFXPointer();
    ActorInfo & actorInfoById(int id);
    int obstacleAt(int x, int y);
    MapData * create_fog_of_war(const MapData &map, ActorInfo current_actor);

    int getGameTurn();
    int getActTurn();
    int getModCounter();
#ifndef TESTING
#define TESTING
protected:
#endif
    //callback function to update the dispaly with the map, actors, and turn count
    void (*displayCallback)(Settings *);
    
    //game functions
    void runMoves(ActorInfo &a, MapData &fog, PositionData &pos);
    void checkObjectRegrowth();
    bool checkObjectStrike(ActorInfo &a);
    bool crate_o_doom(int x, int y, ActorInfo &a);
    bool checkHealth(ActorInfo &a, bool object = true);
    void animateMove(ActorInfo &a);
    void setSPECIAL(const attributes baseStats);
    void nextTurn();
    void addActor(ActorInfo);
    void cull();
    std::vector<ActorInfo> getDeceased(){return deceased;};
    void incTurn();

    //Map functions
    void updateMap();
    void addObstacle(int x, int y, int type = 1);
    void removeObstacle(int x, int y);
    void setMap(MapData * newMap);

    //pointers to other game components
    Game *gameptr = nullptr;
    Settings *settings = nullptr;
    gameTracker *tracker = nullptr;

    //variables
    ActorInfo nullActor = ActorInfo (NULL, "", 0, 0, 0, 0, 0);
    GLfloat y_scalar = 0;
    GLfloat x_scalar = 0;

    std::vector<ActorInfo> actors; /*!< this is all of the actors on the field: tanks + projectiles */
    std::vector<ActorInfo> deceased; /*!< A list of destroyed tanks */
    std::vector<std::pair<int,int>> SFX; /*!< A list of all special effects on the field */
    MapData * fieldMap; /*!< Struct with mapdata, width, height, vector of ints.  0 - empty/ id - actor */

    //Current Match Settings
    int gameTurn = 0; //Current game turn
    int actTurn = 0;
    int modCounter = 7; //Modular counter for animation effects


friend class Game;
};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
