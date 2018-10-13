#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "ActorInfo.h"
#include "GameField.h"
#include "Drawable.h"
#include "Actor.h"
#include "AsciiTankActor.h"
#include "SimpleAI.h"

using namespace std;

enum gameMode {ai, sp, mp};

class Game
{
    public:
        int turn;
        vector <Drawable *> objects;
        vector <Drawable *> obstacles;
        GameField *tankGame;
        gameMode g_mode;

        Game();
        Game(gameMode mode);
        ~Game();

        void makeDrawables();
        void executeTurn();
        void initGameState();
        void closeDown();
        float convertGLXCoordinate( int );
        float convertGLYCoordinate( int );

};

#endif
