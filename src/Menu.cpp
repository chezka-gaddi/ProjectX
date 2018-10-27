/**************************************************************************//**
* @file Menu.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Menu class.
* *****************************************************************************/

#include "Drawable.h"


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
Menu::Menu( int id, int hp, int ammo, int hits )
{
    this->id = id;
    switch(id)
    {
      case 1:
      {
        strncpy(name, "Player 1", 9);
        screen_x = -0.70;
        screen_y = 0.54;
        break;
      }
      case 2:
      {
        strncpy(name, "Player 2", 9);
        screen_x = 1.7;
        screen_y = 0.54;
        break;
      }
      case 3:
      {
        strncpy(name, "Player 3", 9);
        screen_x = -0.70;
        screen_y = .90;
        break;
      }
      case 4:
      {
        strncpy(name, "Player 4", 9);
        screen_x = 1.7;
        screen_y = .90;
      }
    }
    health = hp;
    bullet = ammo;
    score = hits;
    tex = 4;
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
void drawIcon(GLfloat x, GLfloat y, GLuint icon)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x - 0.85, y + 0.65, -5.0f);
    glBindTexture(GL_TEXTURE_2D, gameTex[icon]);
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
    switch (id)
    {
      case 2:
        glScalef(-1, 1, 1);
        break;
      case 3:
        glScalef(-1, -1, 1);
        break;
      case 4:
        glScalef(1, -1, 1);
        break;
    }
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


    // Output name of the player
    switch (id)
    {
      case 1:    
        drawBitmapText(name, screen_x - 0.13, screen_y + 0.11);
        break;
      case 2:
        drawBitmapText(name, screen_x - 1.04, screen_y + 0.11);
        break;
      case 3:
        drawBitmapText(name, screen_x + 0.16, screen_y - 0.25);
        break;
      case 4:  
        drawBitmapText(name, screen_x - 1.32, screen_y - 0.25);
        break;
    }

    // Draw health points
    for( int i = 0; i < health ; i++ )
    {
      switch (id)
      {
        case 1:    
          drawIcon(screen_x - .05 + (0.14 * i), screen_y - 0.02, 4 );
          break;
        case 2:
          drawIcon(screen_x + 0.75 - (0.14 * i), screen_y - 0.02, 4 );
          break;
        case 3:
          drawIcon(screen_x - .05 + (0.14 * i), screen_y + 0.05, 4 );
          break;
        case 4:  
          drawIcon(screen_x + 0.75 - (0.14 * i), screen_y + 0.05, 4 );
          break;
      }
    }

    // Draw number of hits
    for( int i = 0; i < score ; i++ )
    {
      switch (id)
      {
        case 1:    
          drawIcon((screen_x - 0.05) + 0.1 * i, screen_y - 0.18, 6 );
          break;
        case 2:
          drawIcon(screen_x + 0.75 - 0.1 * i, screen_y - 0.18, 6 );
          break;
        case 3:
          drawIcon((screen_x - 0.05) + 0.1 * i, screen_y - 0.10, 6 );
          break;
        case 4:  
          drawIcon(screen_x + 0.75 - 0.1 * i, screen_y - 0.10, 6 );
          break;
      } 
    }
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
