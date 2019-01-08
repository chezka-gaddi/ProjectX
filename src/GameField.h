/**
 * @file GameField.h
 * @author David Donahue
 * @brief GameField manages the play field and  actors.
 */

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <vector>
#include <algorithm>
#include "ProjectileActor.h"
#include "PositionData.h"
#include "Actor.h"
#include "MapData.h"
#include "ActorInfo.h"
#include "direction.h"
#include <iostream>
#include <ctime>
#include <GL/glut.h>
#include <GL/freeglut.h>

/***************************************************************************//**
* @class GameField
* @author David Donahue
* @par Description
* The class that will act as the manager of the gamefield
* *****************************************************************************/

class Game;

class GameField
{

protected:
    /*!< this is all of the actors on the field: tanks + projectiles */
    std::vector<ActorInfo> actors;
    std::vector<ActorInfo> deceased;
    std::vector<std::pair<int,int>> SFX;

    int turnCount = 0; /*!< The turn count number */
    /** struct with width, height, and a vector of ints in
     row major order, 0 for empty tiles and actor id for nonempty. */
    MapData fieldMap;

    //callback function to update the dispaly with the map, actors, and turn count
    void (*displayCallback)(MapData, std::vector<ActorInfo>, int);
    void updateMap();
    void runMoves(ActorInfo &a, MapData &fog, PositionData &pos);
    ActorInfo nullActor = ActorInfo (NULL, 0, 0, 0, 0, 0);
    //Action points for each actor
    int ap;
    GLfloat y_scalar = 0;
    GLfloat x_scalar = 0;
    bool checkObjectStrike(ActorInfo &a);
    bool crate_o_doom(int x, int y, ActorInfo &a);
    bool checkHealth(ActorInfo &a, bool object = true);
    void animateMove(ActorInfo &a);
    Game *gameptr = nullptr;
    //helper functions
    void checkObjectRegrowth();

public:
    void setSPECIAL(int points, const attributes baseStats);
    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all of the tanks have fired
     * it starts over again
     */
    void nextTurn();
    void addActor(ActorInfo);
    void checkForCheaters(int pointsAvailable);
    void addObstacle(int x, int y, int type = 1);
    void removeObstacle(int x, int y);
    /**
     * removes all actors that have a health of 0 from the game (not actors with health less than 0)
     */
    void cull();
    std::string getWinner();
    std::vector<ActorInfo> getDeceased(){return deceased;};

    /**
     * this will find all the actors in a single cell
     * @return vector of actors that all have the same position
     */
    std::vector<ActorInfo> findActorsByCoord(int x, int y);

    /*******************************/
    /********constructors***********/
    /*******************************/

    GameField();
    GameField(int width, int height);
    GameField(int width, int height, std::vector<ActorInfo> startActors);
    GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int));
    GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int), Game *);
    GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int), int ap);
    GameField(int width, int height, std::vector<ActorInfo> startActors, int actionpoints);


    ~GameField();
    /*******************************/
    /*************getters***********/
    /*******************************/

    int getTurnCount();
    int getWidth();
    int getHeight();
    std::vector<int> getMap();
    std::vector<ActorInfo> getActors();
    std::vector<ActorInfo> * getActorsPointer();
    const std::vector<ActorInfo> &getActorsConst();
    std::vector<std::pair<int,int>> getSFX();
    std::vector<std::pair<int,int>> * getSFXPointer();
    const std::vector<std::pair<int,int>> &getSFXConst();
    void clearSFX();
    MapData getMapData();
    ActorInfo & actorInfoById(int id);
    int obstacleAt(int x, int y);
    void create_fog_of_war(MapData &map, ActorInfo current_actor);


    /*******************************/
    /************setters************/
    /*******************************/
friend class Game;
};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
