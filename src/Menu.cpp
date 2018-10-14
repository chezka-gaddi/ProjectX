/**************************************************************************//**
* @file Menu.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Menu class.
* *****************************************************************************/

#include "Drawable.h"
#include <iostream>

void drawBitmapText( char *string, float x, float y );


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initializes the menu with the player the menu is being made for and the stats
* to be printed.
*
* @param[in] id - player id
* @param[in] hp - health
* @param[in] ammo - ammo count
* *****************************************************************************/
Menu::Menu( int id, int hp, int ammo, int hits )
{
    this->id = id;
    if( id == 1 )
    {
        strncpy(name, "Player 1", 9);
        screen_x = -0.7;
    }
    
    else
    {
        strncpy(name, "Player 2", 9);
        screen_x = 0.55;
    }

    screen_y = 0.7;
    health = hp;
    bullet = ammo;
    score = hits;
    tex = 6;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the player stats up in the menu bar.
* *****************************************************************************/
void Menu::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();
    
    drawPlayerStats();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void Menu::drawHeart(GLfloat x, GLfloat y)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x - .50, y + 0.68, -5.0f);  
    glBindTexture(GL_TEXTURE_2D, texture[tex]);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.07f, -0.09f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.07f, -0.09f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.07f,  0.09f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.07f,  0.09f,  1.0f);
	glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawPlayerStats
*
* Edits and displays all of the statistics to the screen.
* *****************************************************************************/
void Menu::drawPlayerStats()
{
    drawBitmapText(name, screen_x, screen_y);
    
    char strHealth[10] = "HP: ";
    drawBitmapText(strHealth, screen_x, screen_y - 0.05);
    
    for( int i = 0; i < health ; i++ )
    {
        if( id == 1 )
            drawHeart(screen_x + 0.12 * i, screen_y - 0.05 );
        
        else
            drawHeart(screen_x + 1.25 + 0.12 * i, screen_y - 0.05 );
    }

    char strAmmo[10] = "Ammo: ";
    char ammo[4];
    sprintf(ammo, "%d", bullet);
    strcat(strAmmo, ammo);
    drawBitmapText(strAmmo, screen_x, screen_y - 0.10);
    
    char hits[4];
    sprintf(hits, "%d", score);
    drawBitmapText(hits, screen_x - 0.1, screen_y - 0.05);
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawBitmapText
*
* Generates all of the string statistics to the screen.
* *****************************************************************************/
void drawBitmapText( char *string, float x, float y )
{
    glDisable(GL_TEXTURE_2D);
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );
    
    for( c = string; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *c );
}
