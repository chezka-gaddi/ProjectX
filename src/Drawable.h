/***************************************************************************//**
* @file Drawable.h
* @author Chezka Gaddi
* @brief Contains all functions prototypes that maintains Drawable class and all
* of it's subclasses
*******************************************************************************/
#ifndef SLACKERS_PLATFORM_DRAWABLE_H
#define SLACKERS_PLATFORM_DRAWABLE_H

#include <cstring>
#include <string>
#include "global.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @class Drawable
* @brief Drawable is the parent class for all GUI objects and has a draw function that
* must be overwritten by subclasses.
*******************************************************************************/
class Drawable
{
public:
    std::string name;   /*!<The name of the drawable */
    int id;             /*!<The id number of the drawable */
    GLfloat screen_x;   /*!<The screen x coordinate of the drawable */
    GLfloat screen_y;   /*!<The scren y coordinate of the drawable */
    int health;         /*!<The health value of the drawable */
    GLuint tex;            /*!<Texture to draw object with */

    Drawable() {}
    ~Drawable() {}

    virtual void draw() = 0; /*!<A pure virtual function to ensure drawable objects define how they are drawn */
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class GameFieldDrawable
* @brief GameField contains instructions to draw the GameField
*******************************************************************************/
class GameFieldDrawable : public Drawable
{
public:
    GLuint tex;
    GameFieldDrawable();

    void draw();
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Menu
* @brief Menu contains instructions to draw the player statistics
*******************************************************************************/
class Menu : public Drawable
{
public:
    char name[9];       /*!<Name of the player to be displayed */
    int health;         /*!<Player's health */
    int bullet;         /*!<Current bullet count */
    int score;          /*!<Current score */

    Menu( int, int, int, int );

    void drawTextBox( GLfloat, GLfloat );
    void drawPlayerStats();
    void draw();
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Obstacles
* @brief Obstacles contains instructions to draw trees or rocks
*******************************************************************************/
class Obstacles : public Drawable
{
public:
    Obstacles( int, GLfloat, GLfloat);

    void draw();
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Projectile
* @brief Projectile contains instructions to draw the Projectiles
*******************************************************************************/
class Projectile : public Drawable
{
public:
    int angle;

    Projectile(int ID, GLfloat x, GLfloat y);

    void draw();
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class TankDrawable
* @brief TankDrawable contains instructions to draw the TankDrawable
*******************************************************************************/
class TankDrawable : public Drawable
{
public:
    int angle;

    TankDrawable( int ID, GLfloat x, GLfloat y);

    void draw();
};



#endif //SLACKERS_PLATFORM_DRAWABLE_H
