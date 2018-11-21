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
#include "direction.h"

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
    int max_health;
    GLuint tex;            /*!<Texture to draw object with */

    Drawable() {}
    ~Drawable() {}

    virtual void draw(int, int) = 0; /*!<A pure virtual function to ensure drawable objects define how they are drawn */
protected:
    int gridx;
    int gridy; 
    static float xscalar;
    static float yscalar;
friend class Game;
friend class GameField;
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

    void draw(int, int);
};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Menu
* @brief Menu contains instructions to draw the player statistics
*******************************************************************************/
class Menu : public Drawable
{
public:
    char name[20];       /*!<Name of the player to be displayed */
    int health;         /*!<Player's health */
    int bullet;         /*!<Current bullet count */
    int score;          /*!<Current score */
    int angle = 0;
    int bTex;
    int turn = 0;

    Menu( int, int, int, int, std::string, direction, int, int);

    void drawTextBox( GLfloat, GLfloat );
    void drawPlayerStats();
    void draw(int, int);

};


/***************************************************************************//**
* @author Chezka Gaddi
* @class Obstacles
* @brief Obstacles contains instructions to draw trees or rocks
*******************************************************************************/
class Obstacles : public Drawable
{
public:
    Obstacles( int, GLfloat, GLfloat, int, int);
    void regrow(int turn); 
    void draw(int, int);
protected:
    int destroyed;
    int regrow_rate;
    void set_destroyed(int d);
friend class GameField;
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

    Projectile(int ID, GLfloat x, GLfloat y, direction dir, bool t);

    void draw(int, int);

    float sizeMod = 1;
    bool turn;
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
    int turn;
    bool sMod;

    TankDrawable( int ID, GLfloat x, GLfloat y, direction dir, int t, bool sMod);

    void draw(int, int);
    void setHealth(int h);
    void setMax_health(int mh);
};

/***************************************************************************//**
* @author Not Chezka Gaddi
* @class sfxDrawable
* @brief sfxDrawable contains instructions to draw the sfxDrawable
*******************************************************************************/
class sfxDrawable : public Drawable
{
public:
    int angle;

    sfxDrawable(GLfloat x, GLfloat y);

    void draw(int, int);
};
/***************************************************************************//**
* @author Not Chezka Gaddi
* @class crate
* @brief crate contains instructions to draw the party crate
*******************************************************************************/
class Crate : public Drawable
{
public:
    int angle;

    Crate(GLfloat x, GLfloat y,int, int);

    void draw(int, int);
};


#endif //SLACKERS_PLATFORM_DRAWABLE_H
