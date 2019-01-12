/***************************************************************************//**
* @file Projectile.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for Projectile class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initiates the coordinates of where projectile is to be drawn and from whom the
* projectile came from.
*
* @param[in] ID - indicates who fired the projectile
* @param[in] x_coor - coordinate to spawn projectile
* @param[in] y_coor - coordinate to spawn projectile
* *****************************************************************************/
Projectile::Projectile( int ID, GLfloat x_coor, GLfloat y_coor, direction dir, bool t, float osx = 1, float osy = 1, bool camp = false)
{ 
    screen_x = x_coor;
    screen_y = y_coor;
    offsetx = osx;
    offsety = osy;
    id = ID;
    turn = t;
    this->camp = camp;

    switch(dir)
    {
    case UP:
        angle = 90;
        break;

    case UPRIGHT:
        angle = 45;
        break;

    case RIGHT:
        angle = 0;
        break;

    case DOWNRIGHT:
        angle = -45;
        break;

    case DOWN:
        angle = -90;
        break;

    case DOWNLEFT:
        angle = -135;
        break;

    case LEFT:
        angle = 180;
        break;

    case UPLEFT:
        angle = 135;
        break;
    case STAY:
    default:
        break; //should never reach here but warning without
    }

    if (camp == true){
      tex = 11;
    }else{
      tex = ((-1 * id) - 1) * 5 + 4;
    }
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the projectile in the gamefield
* @param[in] x The current turn value
* *****************************************************************************/
void Projectile::draw(int x, int y)
{
    float trailMod = .9; //Scale the trail
    
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
    glRotatef(angle,0,0,1);
    //Check if we have a marshmellow 
    if (camp == true)
      glBindTexture(GL_TEXTURE_2D, sfxTex[tex]);
    else
      glBindTexture(GL_TEXTURE_2D, tankTex[tex]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.07f * xscalar * sizeMod, -0.07f * yscalar * sizeMod,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.07f * xscalar * sizeMod, -0.07f * yscalar * sizeMod,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.07f * xscalar * sizeMod,  0.07f * yscalar * sizeMod,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.07f * xscalar * sizeMod,  0.07f * yscalar * sizeMod,  1.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
   
    if (turn == true){ //Only draw trail on projectiles turn
      glEnable(GL_TEXTURE_2D);
      glPushMatrix();
      glBindTexture(GL_TEXTURE_2D, sfxTex[x % 4]);
      glTranslatef(screen_x + offsetx, screen_y + offsety, -5.0f);
      glRotatef(angle,0,0,1);
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(-0.20f * xscalar * sizeMod * trailMod, -0.07f * yscalar * sizeMod * trailMod,  1.0f);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f( -0.06f * xscalar * sizeMod * trailMod, -0.07f * yscalar * sizeMod * trailMod,  1.0f);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f( -0.06f * xscalar * sizeMod * trailMod,  0.07f * yscalar * sizeMod * trailMod,  1.0f);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-0.20f * xscalar * sizeMod * trailMod,  0.07f * yscalar * sizeMod * trailMod,  1.0f);
      glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }
}
