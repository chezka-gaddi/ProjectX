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


//this will eventually be where we make the playing field, but for now to make everything as complete as possible it will be empty
class GameField{
   
protected:
    //this is all of the actors on the field: tanks + projectiles
    std::vector<ActorInfo> actors;
    int turnCount;
    //struct with width, height, and a vector of ints in
    //row major order, 0 for empty tiles and actor id for nonempty.
    MapData fieldMap;
    
    void updateMap();
 
public:
    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all of the tanks have fired
     * it starts over again
     */
    void nextTurn();
    void addActor(ActorInfo);

    /**
     * removes all actors that have a health of 0 from the game (not actors with health less than 0)
     */
    void cull();

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

    /*******************************/
    /*************getters***********/
    /*******************************/

    int getTurnCount();
    int getWidth();
    int getHeight();
    std::vector<int> getMap();
    std::vector<ActorInfo> getActors();
    MapData getMapData();
    

    /*******************************/
    /************setters************/
    /*******************************/

};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
