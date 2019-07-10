/***************************************************************************//**
* @file TankDrawable.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for TankDrawable class.
* *****************************************************************************/

#include "ui/Drawable.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initiates the coordinates of where tank is to be drawn and what it will look
* like.
*
* @param[in] ID - tank id
* @param[in] x_coor - coordinate to spawn tank
* @param[in] y_coor - coordinate to spawn tank
* *****************************************************************************/
TankDrawable::TankDrawable( int ID, GLfloat x_coor, GLfloat y_coor, direction dir, int t = 0, int s = 0, GLfloat osx = 1, GLfloat osy = 1, bool camp = false)
{
    screen_x = x_coor;
    screen_y = y_coor;
    offsetx = osx;
    offsety = osy;
    id = ID;
    turn = t;
    sMod = s;
    this->camp = camp;

    // Acesses the right image for the tanks
    //  0 is the up image,
    //  1 is right,
    //  2 is down,
    //  3 is left.
    angle = dirToDeg(dir) - 90;
    tex = (ID-1) * 3;

    if (camp == true)
        tex = 4;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Generates the tank onto the gamefield
* *****************************************************************************/
void TankDrawable::draw(int x, int y)
{
  glEnable(GL_TEXTURE_2D);
  glColor4ub(255,255,255,255);
  glPushMatrix();

  //draw base
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glLoadIdentity();
  glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
  if (camp == true){
    glBindTexture(GL_TEXTURE_2D, sfxTex[tex]);
  }else{
    glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, tankTex[tex]);
  }
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  //.13 old adjustment

  glVertex3f(-1.0f * scalar, -1.0f * scalar,  1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f( 1.0f * scalar, -1.0f * scalar,  1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f( 1.0f * scalar,  1.0f * scalar,  1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f * scalar,  1.0f * scalar,  1.0f);
  glEnd();

  //draw turret
  if (camp == false){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
    glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, tankTex[tex+1]);
    glBegin(GL_QUADS);
    //.13
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f * scalar, -1.0f * scalar,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f * scalar, -1.0f * scalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f * scalar,  1.0f * scalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f * scalar,  1.0f * scalar,  1.0f);
    glEnd();
  }
  //First smoke    
  if (health <= max_health * .66666){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
    glBindTexture(GL_TEXTURE_2D, sfxTex[12]);

    if (sMod % 2 == 0) {
      drawAddon(-0.05f * xscalar, 0.0f, 0.2f * yscalar, 0.3f * yscalar, 1.0f, 1.0f);
    } else {
      drawAddon(-0.05f * xscalar, 0.0f * xscalar, 0.1f * yscalar, 0.2f * yscalar, 45.0f, 1.0f);
    }
    //second smoke
    if (health <= max_health*.5){ 
      if (sMod % 2 == 1 ) {
        drawAddon(0.0f, 0.05f * xscalar, 0.2f * yscalar, 0.3f * yscalar, 1.0f, 1.0f);
      }else{
        drawAddon(0.0f, 0.05f * xscalar, 0.1f * yscalar, 0.2f * yscalar, 45.0f, 1.0f);
      }
    }
    //fire
    if (health <= max_health*.3){ 
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glLoadIdentity();
        glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
        glBindTexture(GL_TEXTURE_2D, sfxTex[8]);
        
        //sizing width .05  height .05
        //left
        drawAddon(-0.07f * xscalar, -0.02f * xscalar, -0.05f * yscalar, 0.0f, 1.0f, 1.0f);
        
        //right
        drawAddon(0.01f * xscalar, 0.06f * xscalar, 0.01f * yscalar, 0.06f * yscalar, 1.0f, 1.0f);
        
        //middle
        drawAddon(-0.04f * xscalar, 0.01f * xscalar, -0.04f * yscalar, 0.01f * yscalar, 1.0f, 1.0f);
      }
  }
  glDisable(GL_TEXTURE_2D);
  drawHealthBar();
  drawAmmo();
  glPopMatrix();
}

/*****************//*
 * @author Jon McKee
 * @brief allows us to set the drawables health
 * @param[in] h the current health of the object
 *******************/
void TankDrawable::setHealth(int h){health = h;}

/*****************//*
 * @author Jon McKee
 * @brief allows us to set the drawables max health
 * @param[in] mh the max health of the object
 *******************/
void TankDrawable::setMaxHealth(int mh){max_health = mh;}

/*****************//*
 * @author Jon McKee
 * @brief allows us to set the drawables health
 * @param[in] h the current health of the object
 *******************/
void TankDrawable::setAmmo(int a){ammo = a;}

/*****************//*
 * @author Jon McKee
 * @brief allows us to set the drawables max health
 * @param[in] mh the max health of the object
 *******************/
void TankDrawable::setMaxAmmo(int ma){maxAmmo = ma;}

/*****************//*
 * @author Erica Keeble
 * @Modified by Jon McKee
 * @Originally in the-new-tank program for spring 2019.
 * 
 * @brief draws the health and ammo bars above the tanks
 *******************/
void TankDrawable::drawHealthBar()
{
	float remaining_health = ( float ) health / max_health;

  //Shouldn't ever have a 0 and if we do, no need to draw an empty bar
	if ( remaining_health <= 0 )
	{
		return;
	}

	//Draw the bar background
	glLoadIdentity();
	glTranslatef ( screen_x + offsetx, screen_y + 0.1f + offsety, -4.0f );
	glColor3f ( 0.1765f, 0.1882f, 0.2784f );
	glBegin ( GL_QUADS );
	glVertex2f ( -1.0f * scalar, 0.25f * scalar);
	glVertex2f ( 1.0f * scalar, 0.25f * scalar);
	glVertex2f ( 1.0f * scalar, -0.25f * scalar);
	glVertex2f ( -1.0f * scalar, -0.25f * scalar);
	glEnd();

  //Draw the bar
  if (remaining_health >= .66)
	  glColor3f ( 0.1f, 1.0f, 0.4f );
  else if (remaining_health >= .33)
    glColor3f ( 0.0f, 0.5f, 0.0f );
  else
    glColor3f ( 0.8f, 0.0f, 0.1f );

  glBegin ( GL_QUADS );
	glVertex2f ( -.9f * scalar, 0.15f * scalar);
	glVertex2f ( ((remaining_health * 1.9f) - 1) * scalar, 0.15f * scalar);
	glVertex2f ( ((remaining_health * 1.9f) - 1) * scalar, -0.15f * scalar);
	glVertex2f ( -.9f * scalar, -0.15f * scalar);
	glEnd();
	return;
}

void TankDrawable::drawAmmo(){
  int bTex = (id-1) * 3 + 2;
  float ammoSpace = .025;

  // Draw Ammo
  for( int i = 0; i < ammo ; i++ )
  {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef ( screen_x + offsetx + 0.05f, screen_y - 0.1f + offsety + (ammoSpace * i), -5.0f );
    glBindTexture(GL_TEXTURE_2D, tankTex[bTex]);
    glRotatef(0,0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); //bot right
    glVertex3f( 1.0f * scalar, 0.5f * scalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f); //top right
    glVertex3f( 1.0f * scalar,  1.0f * scalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f); //top left
    glVertex3f( 0.5f * scalar,  1.0f * scalar,  1.0f);
    glTexCoord2f(0.0f, 0.0f); //bot left
    glVertex3f( 0.5f * scalar, 0.5f * scalar,  1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
  }
}