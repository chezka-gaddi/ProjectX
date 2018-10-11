#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <ActorInfo.h>
#include <GameField.h>
#include "Drawable.h"
#include <Actor.h>
#include <AsciiTankActor.h>

using namespace std;

class Game
{
    public:
        int turn;
        vector <Drawable *> objects;

        Game();

        void executeTurn();
        void initGameState();
        void closeDown();
};

#endif
