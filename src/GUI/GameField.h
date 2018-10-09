#ifndef _GAMEFIELD_H_
#define _GAMEFIELD_H_

#include <iostream>
#include <GL/glut.h>

using namespace std;

class GameField{
    public:
        int gameTurn;

        GameField(){
        gameTurn = 0;
        }
        ~GameField(){}

        void draw();
        void updateTurn( int );
};

#endif
