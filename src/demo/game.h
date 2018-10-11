#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <vector>
#include "Drawable.h"

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
