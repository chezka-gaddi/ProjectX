/**************************************************************************//**
* @file Menu.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Menu class.
* *****************************************************************************/

#include "Drawable.h"
#include <iostream>


void drawBitmapText( char *string, GLfloat x, GLfloat y );


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
Menu::Menu( int id, int hp, int ammo, int hits, std::string nameIn)
{
    this->id = id;
    for(int j = 0; j < 20; j++)
    	name[j] = '\0';

	int i = 0;

	while(nameIn[i] != '\0')
	{
	name[i] = nameIn[i];
	i++;
	}

	screen_x = -0.70;
	screen_y = 0.54;
    health = hp;
    bullet = ammo;
    score = hits;
    tex = (id-1) * 5 + 0;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the player stats up in the menu bar.
* *****************************************************************************/
void Menu::draw(int x, int y)
{
	glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    drawPlayerStats();

    glPopMatrix();
}



/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawIcon
*
* Draws the health and hit icons.
* *****************************************************************************/
void drawIcon(GLfloat x, GLfloat y, GLuint icon, bool tank)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x - 0.85, y + 0.65, -5.0f);
    if(!tank)
    	glBindTexture(GL_TEXTURE_2D, gameTex[icon]);
    else
    	glBindTexture(GL_TEXTURE_2D, tankTex[icon]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.06f, -0.06f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.06f, -0.06f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.06f,  0.06f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.06f,  0.06f,  1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawTextBox
*
* Draws player stats text box
* *****************************************************************************/
void Menu::drawTextBox(GLfloat x, GLfloat y)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x - .5, y + 0.6, -5.0f);
    glBindTexture(GL_TEXTURE_2D, gameTex[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.22f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.5f, -0.22f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.5f,  0.22f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f,  0.22f,  1.0f);
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
    // Create text box player stats will go in
    drawTextBox(screen_x, screen_y);


    //Output name of the player
    drawBitmapText(name, screen_x - 0.13, screen_y + 0.11);

    // Draw health points
    for( int i = 0; i < health ; i++ )
    {
    	drawIcon(screen_x - .05 + (0.14 * i), screen_y - 0.02, 4, false );
    }

    // Draw number of hits
    for( int i = 0; i < score ; i++ )
    {
    	drawIcon((screen_x - 0.05) + 0.1 * i, screen_y - 0.18, 6, false );
    }

    drawIcon((screen_x + 1), screen_y, tex, true);
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief drawBitmapText
*
* Generates all of the string statistics to the screen.
* *****************************************************************************/
void drawBitmapText( char *string, GLfloat x, GLfloat y )
{
    glDisable(GL_TEXTURE_2D);
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );

    for( c = string; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *c );
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *c );
}
