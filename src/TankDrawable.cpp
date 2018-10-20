/***************************************************************************//**
* @file TankDrawable.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for TankDrawable class.
* *****************************************************************************/

#include "Drawable.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initiates the coordinates of where tank is to be drawn and what it will look
* like.
*
* @param[in] ID - tank id
* @param[in] x_coor - coordinate to spawn tank
* @param[in] y_coor - coordinate to spawn tank
* *****************************************************************************/
TankDrawable::TankDrawable( int ID, GLfloat x_coor, GLfloat y_coor, direction dir )
{
    screen_x = x_coor;
    screen_y = y_coor;
    id = ID;
    

    // Acesses the right image for the tanks
    //  0 is the up image,
    //  1 is right,
    //  2 is down,
    //  3 is left.
    switch(dir)
    {
        case LEFT:
            {
                tex = (ID-1) * 5 + 3;  
            } break;
        case RIGHT:
            {
                tex = (ID-1) * 5 + 1;  
            } break;
        case UP:
            {
                tex = (ID-1) * 5 + 0;  
            } break;
        case DOWN:
            {
                tex = (ID-1) * 5 + 2;  
            } break;
    }

    angle = 0;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Generates the tank onto the gamefield
* *****************************************************************************/
void TankDrawable::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, tankTex[tex]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.13f, -0.1f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.13f, -0.1f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.13f,  0.1f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.13f,  0.1f,  1.0f);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
