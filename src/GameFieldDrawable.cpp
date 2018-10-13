/***************************************************************************//**
* @file GameField.cpp
* @brief Contains all onjects and functions to be drawn with the GameField.
* @author Chezka Gaddi
* *****************************************************************************/

#include "Drawable.h"

GameFieldDrawable::GameFieldDrawable() : tex(2) {}


void GameFieldDrawable::draw()
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
	glBindTexture(GL_TEXTURE_2D, texture[tex]);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.9f, -1.8f,  1.0f);
        glTexCoord2f(0.8f, 0.0f); glVertex3f( 1.9f, -1.8f,  1.0f);
        glTexCoord2f(0.8f, 1.0f); glVertex3f( 1.9f,  0.9f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.9f,  0.9f,  1.0f);
	glEnd();
    glPopMatrix();
}
