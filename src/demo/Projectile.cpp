/**
 * @file TankDrawable.cpp
 * @brief Contains the functions to construct and draw the TankDrawable.
 * @author Chezka Gaddi
 **/

#include "Drawable.h"

/**
 * Will no be used in actual program. Actor class constructor will be used instead
 **/
Projectile::Projectile( int ID, GLfloat x_coor, GLfloat y_coor )
{
    screen_x = x_coor;
    screen_y = y_coor;
    id = ID;
    distance = 0;

    angle = 0;
    if( ID == 2 )
        angle = 180;
}


/**
 * @author Chezka Gaddi
 * @brief Draws the tank according to the texture associated with the tank.
 *
 * @return Void
 **/
void Projectile::draw()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(screen_x, screen_y, -5.0f);  
	glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.13f, -0.1f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.13f, -0.1f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.13f,  0.1f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.13f,  0.1f,  1.0f);
	glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
