/**
 * @file TankDrawable.h
 * @brief Contains the class definition and funtion prototypes for the TankDrawable class
 * @author Chezka Gaddi
 **/

#ifndef _TANKDRAWABLE_H_
#define _TANKDRAWABLE_H_

#include <GL/glut.h>

#include "global.h"

/**
 * @class TankDrawable
 * @brief A class that describes and draws the tanks.
 * @author Chezka Gaddi
 **/
class TankDrawable
{
    public:
        GLfloat screen_x, screen_y;     /*!< The x and y coordinates that the tank starts at */
        int tankID;                     /*!< The identifier of the tank */
        int angle;
        
        /**
         * Will be replaced by the Actor constructor
         **/
        TankDrawable( int ID, GLfloat x, GLfloat y);
        
        
        /**
         * @brief The destructor for the TankDrawable class
         * @author Chezka Gaddi
         **/
        ~TankDrawable(){}
        
        
        /**
        * @brief Draws the tank according to the texture associated with the tank.
        * @return Void
        **/
        void draw();
};

#endif //_TANKDRAWABLE_H_
