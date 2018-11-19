/***************************************************************************//**
* @file TankDrawable.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for TankDrawable class.
* *****************************************************************************/

#include "Drawable.h"


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
TankDrawable::TankDrawable( int ID, GLfloat x_coor, GLfloat y_coor, direction dir, int t = 0, bool s = false )
{
    screen_x = x_coor;
    screen_y = y_coor;
    id = ID;
    turn = t;
    sMod = s;

    // Acesses the right image for the tanks
    //  0 is the up image,
    //  1 is right,
    //  2 is down,
    //  3 is left.
    angle = 0;
    switch(dir)
    {
    case LEFT:
    {
        tex = (ID-1) * 5 + 3;
    }
    break;
    case RIGHT:
    {
        tex = (ID-1) * 5 + 1;
    }
    break;
    case UPRIGHT:
    {
        tex = (ID-1) * 5 + 0;
        angle = 45;
    }
    break;
    case DOWNRIGHT:
    {
        tex = (ID-1) * 5 + 2;
        angle = -45;
    }
    break;
    case UPLEFT:
    {
        tex = (ID-1) * 5 + 0;
        angle = -45;
    }
    break;
    case DOWNLEFT:
    {
        tex = (ID-1) * 5 + 2;
        angle = 45;
    }
    break;
    case UP:
    {
        tex = (ID-1) * 5 + 0;
    }
    break;
    case DOWN:
    {
        tex = (ID-1) * 5 + 2;
    }
    break;
    default:
        tex = ID-1 * 5;
    }

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    glRotatef(angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D, tankTex[tex]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.13f * scalar, -0.1f * scalar,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.13f * scalar, -0.1f * scalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.13f * scalar,  0.1f * scalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.13f * scalar,  0.1f * scalar,  1.0f);
    glEnd();
    //First smoke    
    if (health <= max_health*.66666){
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glLoadIdentity();
      glTranslatef(screen_x, screen_y, -5.0f);
      glBindTexture(GL_TEXTURE_2D, sfxTex[3]);

      if (sMod == 0) {
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.05f * scalar, .3f * scalar,  1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 0.0f * scalar, .3f * scalar,  1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 0.0f * scalar,  0.2f * scalar,  1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.05f * scalar,  0.2f * scalar,  1.0f);
        glEnd();
      } else {
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.05f * scalar, .2f * scalar,  1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 0.0f * scalar, .2f * scalar,  1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 0.0f * scalar,  0.1f * scalar,  1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.05f * scalar,  0.1f * scalar,  1.0f);
        glEnd();
      }
      //second smoke
      if (health <= max_health*.5){ 
        if (sMod != 0) {
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-0.0f * scalar, .3f * scalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.05f * scalar, .3f * scalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.05f * scalar,  0.2f * scalar,  1.0f);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-0.0f * scalar,  0.2f * scalar,  1.0f);
          glEnd();
        }else{
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-0.0f * scalar, .2f * scalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.05f * scalar, .2f * scalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.05f * scalar,  0.1f * scalar,  1.0f);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-0.0f * scalar,  0.1f * scalar,  1.0f);
          glEnd();
        }
      }
      //fire
      //if (health <= max_health*.3){ 
      if (health <= max_health){ 
          glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
          glLoadIdentity();
          glTranslatef(screen_x, screen_y, -5.0f);
          glBindTexture(GL_TEXTURE_2D, sfxTex[8]);
          
          //sizing width .05  height .05
          //left
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f( -0.07f * scalar, -0.05f * scalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( -0.02f * scalar, -0.05f * scalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( -0.02f * scalar,  0.0f * scalar,  1.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f( -0.07f * scalar,  0.0f * scalar,  1.0f);
          glEnd();
          
          //right
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f( 0.01f * scalar, 0.01f * scalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.06f * scalar, 0.01f * scalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.06f * scalar,  0.06f * scalar,  1.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f( 0.01f * scalar,  0.06f * scalar,  1.0f);
          glEnd();
          
          //middle
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f( -0.04f * scalar, -0.04f * scalar,  1.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f( 0.01f * scalar, -0.04f * scalar,  1.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f( 0.01f * scalar,  0.01f * scalar,  1.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f( -0.04f * scalar,  0.01f * scalar,  1.0f);
          glEnd();
        }
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void TankDrawable::setHealth(int h){health = h;}
void TankDrawable::setMax_health(int mh){max_health = mh;}
