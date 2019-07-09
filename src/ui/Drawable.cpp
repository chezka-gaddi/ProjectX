#include "Drawable.h"

int Drawable::dirToDeg(direction d){
    switch (d){
        case UP:
            return 90;
        case UPRIGHT:
            return 45; 
        case RIGHT:
            return 0;
        case DOWNRIGHT:
            return -45;
        case DOWN:
            return -90;
        case DOWNLEFT:
            return -135;
        case LEFT:
            return 180;
        case UPLEFT:
            return 135;
        //Uknown direction for degrees defaulting to up
        case STAY:
        default:
            return 90;
    }
}

/***************************************************************************//**
* @author Jon McKee
* @brief drawAddon(float xlow, float xhigh, flot ylow, float yhigh, float rot, float scale)
*
* draws the box location of any additional item needed to be added to a drawable object.
* @param[in] xlow The lower x value
* @param[in] xhigh The higher x value
* @param[in] ylow The lower y value
* @param[in] yhigh The higher y value
* @param[in] rot The rotation amount
* @param[in] scale The scale amount
* *****************************************************************************/
void Drawable::drawAddon(float xlow, float xhigh, float ylow, float yhigh, float rot = 1.0, float scale = 1.0)
{
  glBegin(GL_QUADS);
    glRotatef(rot, 0, 0, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( xlow, ylow,  scale);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( xhigh, ylow,  scale);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( xhigh, yhigh,  scale);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( xlow, yhigh,  scale);
  glEnd();
}

void Drawable::updateScalar(){
    if (xscalar > yscalar){
      scalar = yscalar;
    }else{
      scalar = xscalar;
    }
}