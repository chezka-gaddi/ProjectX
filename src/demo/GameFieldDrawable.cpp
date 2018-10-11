/***************************************************************************//**
* @file GameField.cpp
* @brief Contains all onjects and functions to be drawn with the GameField.
* @author Chezka Gaddi
* *****************************************************************************/

#include "Drawable.h"
#include <cstring>

void drawLine( float x, float y );
void gameStatus( int turn );
void drawLargeBitmapText( char *str, float x, float y );

void GameFieldDrawable::draw()
{
    glDisable(GL_TEXTURE_2D);
    gameStatus(gameTurn);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.8f, -1.8f,  1.0f);
        glTexCoord2f(0.8f, 0.0f); glVertex3f( 1.8f, -1.8f,  1.0f);
        glTexCoord2f(0.8f, 1.0f); glVertex3f( 1.8f,  0.9f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.8f,  0.9f,  1.0f);
	glEnd();
    glPopMatrix();
}


void gameStatus( int turn )
{
    char str[15];
    glPushMatrix();

    if( turn % 2 == 0 )
        strncpy(str, "Ready Player 1", 15);

    else
        strncpy(str, "Ready Player 2", 15);

    drawLargeBitmapText( str, -0.1, -0.96 );

    glPopMatrix();
}


void GameFieldDrawable::updateTurn( int turn )
{
    gameTurn = turn;
}


void drawLargeBitmapText( char *str, float x, float y )
{
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );

    for( c = str; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *c );
}
