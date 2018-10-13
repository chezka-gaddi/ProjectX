
#ifndef SLACKERS_PLATFORM_DRAWABLE_H
#define SLACKERS_PLATFORM_DRAWABLE_H

#include <string>
#include "global.h"


class Drawable{
    public:
        std::string name;   /*!<The name of the drawable */
        int id;             /*!<The id number of the drawable */
        GLfloat screen_x;   /*!<The screen x coordinate of the drawable */
        GLfloat screen_y;   /*!<The scren y coordinate of the drawable */
        int health;         /*!<The health value of the drawable */
        
        Drawable(){}
        ~Drawable(){}

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
        char name[9];
        int health;
        int bullet;
        GLfloat screen_x;
        GLfloat screen_y;

        Menu(){};
        Menu( int, int, int );

        /**
         * @brief The destructor for the Menu class
         * @author Chezka Gaddi
         **/
        ~Menu(){}

        void drawPlayerStats();
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
        /**
         * Will be replaced by the Actor constructor
         **/
        Obstacles( GLfloat x, GLfloat y);


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
        int tex;

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
