/***************************************************************************//**
* @file Projectile.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for Projectile class.
* *****************************************************************************/

#include "Drawable.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initiates the coordinates of where projectile is to be drawn and from whom the
* projectile came from.
*
* @param[in] ID - indicates who fired the projectile
* @param[in] x_coor - coordinate to spawn projectile
* @param[in] y_coor - coordinate to spawn projectile
* *****************************************************************************/
Projectile::Projectile( int ID, GLfloat x_coor, GLfloat y_coor, direction dir )
{
    screen_x = x_coor;
    screen_y = y_coor;
    id = ID;

    switch(dir)
    {
    case UP:
        angle = 90;
        break;

    case UPRIGHT:
        angle = 45;
        break;

    case RIGHT:
        angle = 0;
        break;
    
    case DOWNRIGHT:
        angle = -45;
        break;
    
    case DOWN:
        angle = -90;
        break;
    
    case DOWNLEFT:
        angle = -135;
        break;
    
    case LEFT:
        angle = 180;
        break;
    
    case UPLEFT:
        angle = 135;
        break;
    }
    tex = 8;
    
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the projectile in the gamefield
* *****************************************************************************/
void Projectile::draw()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(screen_x, screen_y, -5.0f);
    glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, tankTex[tex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.07f, -0.07f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.07f, -0.07f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.07f,  0.07f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.07f,  0.07f,  1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
