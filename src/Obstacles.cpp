/**
 * @file TankDrawable.cpp
 * @brief Contains the functions to construct and draw the TankDrawable.
 * @author Chezka Gaddi
 **/

#include "Drawable.h"

Obstacles::Obstacles(GLfloat x_coor, GLfloat y_coor )
{
    screen_x = x_coor;
    screen_y = y_coor;
}


/**
 * @author Chezka Gaddi
 * @brief Draws the obstacle according to the texture associated with the tank.
 *
 * @return Void
 **/
void Obstacles::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    glBindTexture(GL_TEXTURE_2D, texture[3]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.18f, -0.23f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.18f, -0.23f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.18f,  0.23f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.18f,  0.23f,  1.0f);
	glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
