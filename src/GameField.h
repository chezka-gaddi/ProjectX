//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <vector>
#include "Actor.h"
#include "TankActor.h"
#include "ProjectileActor.h"
#include "PositionData.h"


//this will eventually be where we make the playing field, but for now to make everything as complete as possible it will be empty
class GameField{
    int idCount;//mostly for the creation of more actors, each actor needs an id and it would be best if each id was different

protected:
    //this is all of the actors on the field: tanks + projectiles
    std::vector<Actor*> actors;
    int turn;
public:
    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all of the tanks have fired
     * it starts over again
     */
    void nextTurn();
    /***
     *
     * returns a vector of the position of all of the actors on the game field
     * @return vector<PositionData> the state of each actor on the field
     */
    std::vector<PositionData> currentGameState();

};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
