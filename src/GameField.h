//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <vector>
#include <algorithm>
#include "PositionData.h"
#include "Actor.h"


//this will eventually be where we make the playing field, but for now to make everything as complete as possible it will be empty
class GameField{
   
protected:
    //this is all of the actors on the field: tanks + projectiles
    std::vector<Actor *> actors;
    int turnCount;
    int fieldWidth, fieldHeight;
    //row major order, 0 for empty tiles and actor id for nonempty.
    std::vector<int> map;
    
    
public:
    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all of the tanks have fired
     * it starts over again
     */
    void nextTurn();
    void addActor(Actor *);
    /**
     *
     * returns a vector of the position of all of the actors on the game field
     * @return vector<PositionData> the state of each actor on the field
     */
    std::vector<PositionData> currentGameState();

    /**
     * removes all actors that have a health of 0 from the game (not actors with health less than 0)
     */
    void cull();

    /**
     * this will find all the actors in a single cell
     * @return vector of actors that all have the same position
     */
    std::vector<Actor*> findActorsByCoord(int x, int y);

    /*******************************/
    /********constructors***********/
    /*******************************/

    GameField();
    GameField(int width, int height);


    /*******************************/
    /*************getters***********/
    /*******************************/

    int getTurnCount();
    int getWidth();
    int getHeight();
    std::vector<int> getMap();
    std::vector<Actor *> getActors();

    /*******************************/
    /************setters************/
    /*******************************/

};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
