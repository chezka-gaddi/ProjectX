//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_TANK_H
#define SLACKERS_PLATFORM_TANK_H

#include "Drawable.h"
#include "Actor.h"
#include "GameField.h"

/**
 * Tank class handles the tank
 */
class Tank: public Drawable, public Actor{
public:

    /**
     * draws the tank
     */
    void draw();

    /**
     * handles the turns for the tank
     * \param gameField the game field where the tank exists
     */
    void move(GameField& gameField);
};


#endif //SLACKERS_PLATFORM_TANK_H
