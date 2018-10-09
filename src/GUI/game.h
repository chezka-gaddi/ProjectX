#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include <vector>
#include "TankDrawable.h"

using namespace std;

class Game
{

    public:
        int turn;
        vector <TankDrawable> tanks;
        Game();

        void executeTurn();
        void initGameState();
        void closeDown();
};

#endif
