/***************************************************************************//**
* @file Crate.cpp
* @author Jon McKee
* @brief Contains all maintenance functions for Crate class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Jon McKee
* @brief Constructor
*
* Initiates the coordinates of where crate is to be drawn and from whom the
* crate came from.
*
* @param[in] ID - indicates who fired the crate
* @param[in] x_coor - coordinate to spawn crate
* @param[in] y_coor - coordinate to spawn crate
* *****************************************************************************/
Crate::Crate( GLfloat x_coor, GLfloat y_coor )
{
    screen_x = x_coor;
    screen_y = y_coor;
    tex = 4;
    health = 1;
}


/***************************************************************************//**
* @author Jon McKee
* @brief draw
*
* Draws the crate in the gamefield
* *****************************************************************************/
void Crate::draw(int x, int y)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(screen_x, screen_y, -5.0f);
    glBindTexture(GL_TEXTURE_2D, sfxTex[tex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.12f * scalar, -0.14f * scalar,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.12f * scalar, -0.14f * scalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.12f * scalar,  0.14f * scalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.12f * scalar,  0.14f * scalar,  1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
