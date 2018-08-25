//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_PROJECTILE_H
#define SLACKERS_PLATFORM_PROJECTILE_H

#include "Drawable.h"
#include "Actor.h"

class Projectile: public Drawable, public Actor{
public:
    /**
     * draws the projectile
     */
    void draw();
    /*
     * projectiles need to be actors like tanks, but they dont get to move the same as tanks
     */
    void move(GameField & gameField);
};
#endif //SLACKERS_PLATFORM_PROJECTILE_H
