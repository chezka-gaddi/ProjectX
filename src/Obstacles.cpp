/***************************************************************************//**
* @file Obstacles.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Obstacles class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
* 
* Initializes the x and y coordinates where the obstacle will be spawned.
*
* @param[in] x_coor - coordinate to spawn obstacle
* @param[in] y_coor - coordinate to spawn obstacle
* *****************************************************************************/
Obstacles::Obstacles(int id, GLfloat x_coor, GLfloat y_coor )
{
    screen_x = x_coor;
    screen_y = y_coor;
    
    tex = 3;
    if(id == 2)
        tex = 7;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
* 
* Draws the obstacle will be into the gamefield.
* *****************************************************************************/
void Obstacles::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    glBindTexture(GL_TEXTURE_2D, texture[tex]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.18f, -0.20f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.18f, -0.20f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.18f,  0.20f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.18f,  0.20f,  1.0f);
	glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
