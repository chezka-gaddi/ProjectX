//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_GAMEFIELD_H
#define SLACKERS_PLATFORM_GAMEFIELD_H

#include <vector>
#include "Actor.h"
#include "Tank.h"


//this will eventually be where we make the playing field, but for now to make everything as complete as possible it will be empty
class GameField{


protected:
    //this is all of the actors on the field: tanks + projectiles
    std::vector<Actor*> actors;

public:
    /**
     * Each turn will be as follows:
     * a tank will have the option to move and then a tank will fire, once all of the tanks have fired
     * it starts over again
     */
    void nextTurn();

};
#endif //SLACKERS_PLATFORM_GAMEFIELD_H
