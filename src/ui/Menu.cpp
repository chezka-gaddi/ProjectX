/**************************************************************************//**
* @file Menu.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Menu class.
* *****************************************************************************/

#include "ui/Drawable.h"
#include <iostream>


void drawBitmapText( char *string, GLfloat x, GLfloat y );
void drawBitmapTurn( int turn, GLfloat x, GLfloat y );


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
Menu::Menu( int id, int hp, int ammo, int hits, std::string nameIn, direction dir, int mc, int t)
{
  this->id = id;
  //for(int j = 0; j < 20; j++)
  // 	name[j] = '\0';
  turn = t;

	unsigned int i = 0;

	while(i < nameIn.size() && i < 20)
	{
    if (nameIn[i] == '\n')
      break;
	  name[i] = nameIn[i];
	  i++;
	}
  name[i] = '\0';

	screen_x = -0.70;
	screen_y = 0.54;
  health = hp;
  bullet = ammo;
  score = hits;
  angle = 180; //up
  id > 0 ? bTex = (id-1) * 3 + 2 : bTex = (-id-1) * 3 + 2;
  id > 0 ? i = id : i = -id;
  
  tex = (i-1) * 3;

  if (mc == 1)
    angle = 135;
  else if (mc == 2)
    angle = 90;
  else if (mc == 3)
    angle = 45;
  else if (mc == 4)
    angle = 0;
  else if (mc == 5)
    angle = -45;
  else if (mc == 6)
    angle = -90;
  else if (mc == 7)
    angle = -135;

  angle = dirToDeg(dir) - 90;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the player stats up in the menu bar.
* *****************************************************************************/
void Menu::draw(int x, int y)
{
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
void drawIcon(GLfloat x, GLfloat y, GLuint icon, bool tank, int angle = 1)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x - 0.85, y + 0.97, -5.0f);
    if(!tank)
    	glBindTexture(GL_TEXTURE_2D, gameTex[icon]);
    else
    	glBindTexture(GL_TEXTURE_2D, tankTex[icon]);
    glRotatef(angle,0,0,1);
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
* @author Jon McKee
* @brief drawAmmo
*
* Draws the Ammo counter.
* *****************************************************************************/
void drawAmmo(GLfloat x, GLfloat y, GLuint icon, bool tank, int angle = 1)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x - 0.85, y + 0.97, -5.0f);
    glBindTexture(GL_TEXTURE_2D, tankTex[icon]);
    glRotatef(angle,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.04f, -0.06f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.06f, -0.06f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.06f,  0.03f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.04f,  0.03f,  1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
/***************************************************************************//**
* @author Jon McKee
* @brief drawTank
*
* Draws the spinning tank.
* *****************************************************************************/
void drawTank(GLfloat x, GLfloat y, GLuint icon, bool tank, int angle)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    if(!tank) //false = bullet  true = tank
    	glBindTexture(GL_TEXTURE_2D, tankTex[icon]);
    else
    	glBindTexture(GL_TEXTURE_2D, tankTex[icon]);
    
    glLoadIdentity();
    
    glTranslatef(x - 1.55, y + 0.95, -5.0f);
    //glTranslatef(-.5, .5, -5.0f);
    glRotatef(angle, 0, 0, 1);
    //glTranslatef(.5, -.5, 5.0f);
    

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.15f, -0.15f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.15f, -0.15f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.15f,  0.15f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.15f,  0.15f,  1.0f);
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
  glTranslatef(x - .55, y + 0.8, -5.0f);
  glBindTexture(GL_TEXTURE_2D, gameTex[3]);
  glBegin(GL_QUADS);
  glVertex3f( -0.5f,  0.0f,  1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f( 4.0f,  0.0f,  1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f( 4.0f,  0.4f,  1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f( -0.5f,  0.4f,  1.0f);
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
    drawBitmapText(name, screen_x - 0.13, screen_y + 0.24);
    
    //Output turn
    drawBitmapTurn(turn, screen_x + 1.40, screen_y + 0.24);

    // Draw health points
    for( int i = 0; i < health ; i++ )
    {
      if (i <= 5){
    	  drawIcon(screen_x + .57 + (0.14 * i), screen_y - 0.04, 2, false );
      }else{
        drawIcon(screen_x + .57 + (0.14 * (5 - (i - 6))), screen_y + 0.08, 2, false );
      }
    }

    // Draw number of hits
    //for( int i = 0; i < score ; i++ )
    //{
    //	drawIcon((screen_x + 2.05) + 0.1 * i, screen_y - 0.04, 4, false );
    //}

    // Draw Ammo
    for( int i = 0; i < bullet ; i++ )
    {
      drawAmmo((screen_x + 1.38) + 0.1 * i, screen_y - 0.04, bTex, true, 90 );
    }

   drawTank((screen_x + 3.25), screen_y, tex, true, angle);
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

/***************************************************************************//**
* @author Jon McKee
* @brief drawBitmapText
*
* Generates the turn string.
* *****************************************************************************/
void drawBitmapTurn( int turn, GLfloat x, GLfloat y )
{
    glDisable(GL_TEXTURE_2D);
    std::string temp = "Turn: ";
    if (turn < 10)
            temp += "  ";
    else if (turn < 100)
            temp += " ";
    temp += std::to_string(turn);
    const char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );

    for( c = temp.c_str(); *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *c );
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *c );
}
