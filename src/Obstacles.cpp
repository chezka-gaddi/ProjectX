/***************************************************************************//**
* @file Obstacles.cpp
* @author Chezka Gaddi
* @brief Contains all maintenance functions for the Obstacles class.
* *****************************************************************************/

#include "Drawable.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Initializes the x and y coordinates where the obstacle will be spawned.
*
* @param[in] x_coor - coordinate to spawn obstacle
* @param[in] y_coor - coordinate to spawn obstacle
* *****************************************************************************/
Obstacles::Obstacles(int id, GLfloat x_coor, GLfloat y_coor, int gx, int gy )
{
    //id's:
    // 0 = Tree   1 = Rocks   2 = Bushes  3 = Other
    //Textures:
    //0-9   Trees  - Packaged Trees  0-3   - 4 Trees
    //10-19 Rocks  - Packaged Rocks  10-12 - 3 Rocks
    //20-29 Bushes - Packaged Bushes 20-23 - 4 Bushes
    screen_x = x_coor;
    screen_y = y_coor;
    gridx = gx;
    gridy = gy;
    if (id == 0){ //It's a tree
      health = 2;
      tex = ((rand() % 4));
    }else if( id == 1){ //It's a Rocks
      health = 4;
      tex = ((rand() % 3) + 10);
    }else if( id == 2){ //It's a Bushes
      tex = ((rand() % 4) + 20);
    }else{
      tex = 1; //default to tree if we got a bad id
    }
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief draw
*
* Draws the obstacle will be into the gamefield.
* *****************************************************************************/
void Obstacles::draw(int, int)
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();
    glTranslatef(screen_x, screen_y, -5.0f);
    if (tex >= 0 && tex <= 9){ //It's a tree
      glBindTexture(GL_TEXTURE_2D, treeTex[tex]);
    }else if( tex >= 10 && tex <= 19){ //It's a Rocks
      glBindTexture(GL_TEXTURE_2D, rockTex[tex-10]);
    }else if( tex >= 20 && tex <= 29){ //It's a Bushes
      glBindTexture(GL_TEXTURE_2D, bushTex[tex-20]);
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.16f * scalar, -0.19f * scalar,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.16f * scalar, -0.19f * scalar,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.16f * scalar,  0.19f * scalar,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.16f * scalar,  0.19f * scalar,  1.0f);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
