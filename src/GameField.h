//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <vector>
#include "PositionData.h"
#include "Actor.h"


//this will eventually be where we make the playing field, but for now to make everything as complete as possible it will be empty
class GameField{
    /**
     * on construction of game field this should be set to 0
     */
    int idCount;//mostly for the creation of more actors, each actor needs an id and it would be best if each id was different

protected:
    //this is all of the actors on the field: tanks + projectiles
    std::vector<Actor *> actors;
    int turnCount;
public:
    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all of the tanks have fired
     * it starts over again
     */
    void nextTurn();
    void runMoves();
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
    std::vector<Actor*> findActorsByCoord();

    /*******************************/
    /********constructors***********/
    /*******************************/

    GameField();


    /*******************************/
    /*************getters***********/
    /*******************************/

    int getTurnCount();

    std::vector<Actor *> getActors();

    /*******************************/
    /************setters************/
    /*******************************/

};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
