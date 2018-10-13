#include "Drawable.h"
#include <iostream>

using namespace std;

void drawBitmapText( char *string, float x, float y );
void drawPlayerStats();


void Menu::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(-0.1, 0.8, -5.0f);  
    glBindTexture(GL_TEXTURE_2D, texture[4]);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.2f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.2f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 0.9f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 0.9f,  1.0f);
	glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void drawPlayerStats()
{
    /*glPushMatrix();
    glColor3f( 0.0, 1.0, 1.0 );
    glBegin(GL_QUADS);
        glVertex3f(-0.9,0.75,-2);
        glVertex3f(-0.9,0.87,-2);
        glVertex3f(-0.7,0.87,-2);
        glVertex3f(-0.7,0.75,-2);
    glEnd();
    glPopMatrix();*/
    
    char str[] = "Player 1";
    drawBitmapText( str, -0.8, 0.7);
}


void drawBitmapText( char *string, float x, float y )
{
    glDisable(GL_TEXTURE_2D);
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );
    
    for( c = string; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *c );
}
