/***************************************************************************//**
* @file GameField.cpp
* @brief Contains all onjects and functions to be drawn with the GameField.
* @author Chezka Gaddi
* *****************************************************************************/

#include "GameField.h"
#include "global.h"
#include <string.h>

void fieldDimensions();
void drawBitmapText( char *string, float x, float y );
void drawLine( float x, float y );
void gameStatus( int turn );
void drawLargeBitmapText( char *string, float x, float y );

void GameField::draw()
{
    glDisable(GL_TEXTURE_2D);
    fieldDimensions();
    gameStatus(gameTurn);
    glEnable(GL_TEXTURE_2D);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);  
	glBindTexture(GL_TEXTURE_2D, texture[1]);
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
    glPushMatrix();
    if( turn % 2 == 0 )
        drawLargeBitmapText( "Ready Player 1", -0.1, -0.96 );

    else
        drawLargeBitmapText( "Ready Player 2", -0.1, -0.96 );
    glPopMatrix();
}


void GameField::updateTurn( int turn )
{
    gameTurn = turn;
}


void drawLargeBitmapText( char *string, float x, float y )
{
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );
    
    for( c = string; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *c );
}


void drawBitmapText( char *string, float x, float y )
{
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );
    
    for( c = string; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *c );
}


void fieldDimensions()
{
    char *arr[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19"};
    float x_start = 0.37;
    float y_start = -0.86;

    glPushMatrix();
    for( int i = 0; i < 10; i++ )
    {
        drawBitmapText( arr[i], -0.95, x_start );
        x_start -= 0.13;
    }
    
    y_start = -0.86;

    for( int j = 0; j < 20; j++ )
    {
        drawBitmapText( arr[j], y_start, 0.52 );
        y_start += 0.09;
    }
    
    glPopMatrix();
}
