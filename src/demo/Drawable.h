//
// Created by jlee on 8/25/18.
//

/** @file */

#ifndef SLACKERS_PLATFORM_DRAWABLE_H
#define SLACKERS_PLATFORM_DRAWABLE_H

#include <string>
#include "global.h"

class Drawable{
//protected:
    public:
    Drawable(){}
    ~Drawable(){}

    std::string name;   /*!<The name of the drawable */
    int id;             /*!<The id number of the drawable */
    GLfloat screen_x;   /*!<The screen x coordinate of the drawable */
    GLfloat screen_y;   /*!<The scren y coordinate of the drawable */
    int health;         /*!<The health value of the drawable */

    //this is for the future, if we dont need it, then we can delete it later it will be used for easy hiding of objects
    bool to_draw;       /*!<The variable deciding whether or not to draw the drawable */

//public:

    virtual void draw() = 0; /*!<A pure virtual function to ensure drawable objects define how they are drew */
};


class GameFieldDrawable : public Drawable
{
    public:
        int gameTurn;

        GameFieldDrawable()
        {
            gameTurn = 0;
        }

        ~GameFieldDrawable(){}

        void updateTurn( int );
        void draw();
};




/**
 * @class Menu
 * @brief A class that describes and draws the tanks.
 * @author Chezka Gaddi
 **/
class Menu : public Drawable
{
    public:
        int angle;
        GLfloat target_x, target_y;
        int distance;

        Menu(){};
        /**
         * Will be replaced by the Actor constructor
         **/

        /**
         * @brief The destructor for the TankDrawable class
         * @author Chezka Gaddi
         **/
        ~Menu(){}

        void draw();
};


/**
 * @class TankDrawable
 * @brief A class that describes and draws the tanks.
 * @author Chezka Gaddi
 **/
class Obstacles : public Drawable
{

    public:
        int angle;
        int tex;
        /**
         * Will be replaced by the Actor constructor
         **/
        Obstacles( int ID, GLfloat x, GLfloat y);


        /**
         * @brief The destructor for the Obstacles class
         * @author Chezka Gaddi
         **/
        ~Obstacles(){}


        /**
        * @brief Draws the tank according to the texture associated with the tank.
        * @return Void
        **/
        void draw();
};


/**
 * @class TankDrawable
 * @brief A class that describes and draws the tanks.
 * @author Chezka Gaddi
 **/
class Projectile : public Drawable
{
    public:
        int angle;
        GLfloat target_x, target_y;
        int distance;

        Projectile(){};
        /**
         * Will be replaced by the Actor constructor
         **/
        Projectile( int ID, GLfloat x, GLfloat y);


        /**
         * @brief The destructor for the TankDrawable class
         * @author Chezka Gaddi
         **/
        ~Projectile(){}

        void draw();
};


/**
 * @class TankDrawable
 * @brief A class that describes and draws the tanks.
 * @author Chezka Gaddi
 **/
class TankDrawable : public Drawable
{
    public:
        int angle;
        int tex;

        /**
         * Will be replaced by the Actor constructor
         **/
        TankDrawable( int ID, GLfloat x, GLfloat y);


        /**
         * @brief The destructor for the TankDrawable class
         * @author Chezka Gaddi
         **/
        ~TankDrawable(){}

        void draw();
};



#endif //SLACKERS_PLATFORM_DRAWABLE_H
