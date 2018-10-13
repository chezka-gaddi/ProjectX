#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "SOIL.h" 
 
void display(void);
void init(void);
void reshape(int w,int h);
 
GLuint texture_id;
GLuint texShips[1];
 
int main(int argc,char **argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize(512,512);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
  glutCreateWindow("Transparency test");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  init();
  glutMainLoop();
 
  return(EXIT_SUCCESS);
}
 

void init(void)
{
    texShips[0] = SOIL_load_OGL_texture(
        "tank.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
        //SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
    );
    if (texShips[0] == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
    }
}


void drawShips()
{
    glColor4ub(255, 255, 255, 255);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLoadIdentity();              

    glTranslatef(6.0f, 2.0f, -12.0f);

    glBindTexture(GL_TEXTURE_2D, texShips[0]);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-4.0f, 3.0f, 2.0);

    glTexCoord2f(0, 1);
    glVertex3f(-4.0f, -2.3, 2.0);

    glTexCoord2f(1, 1);
    glVertex3f(1.0, -2.3, 2.0);

    glTexCoord2f(1, 0);
    glVertex3f(1.0, 3.0, 2.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
} 
/*---------------------------------------------------*/
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(0.0,0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);
 
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glColor4f(1.0,1.0,1.0,1.0);
  glTranslatef(-1.5,-1.5,-0.25);
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(-5.0,-5.0,0.0);
  glVertex3f(5.0,-5.0,0.0);
  glVertex3f(-5.0,5.0,0.0);
  glVertex3f(5.0,5.0,0.0); 
  glEnd();
  glPopMatrix(); 
 
	glPushMatrix(); 
	drawShips();
	glPopMatrix();
  /*glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture_id);
  glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0,1.0,1.0,0.5);//Replace this alpha for transparency
  glBegin(GL_TRIANGLE_STRIP);
  glTexCoord2f(0.0,0.0);
  glVertex3f(-5.0,-5.0,0.0);
  glTexCoord2f(1.0,0.0);
  glVertex3f(5.0,-5.0,0.0);
  glTexCoord2f(0.0,1.0);
  glVertex3f(-5.0,5.0,0.0);
  glTexCoord2f(1.0,1.0);
  glVertex3f(5.0,5.0,0.0); 
  glEnd();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);   
  glPopMatrix();
 */
 
  glutSwapBuffers();
}
 
 
/*------------------------------------------------------*/
/*void init(void)
{
  glEnable(GL_DEPTH_TEST);
 
  std::vector<GLubyte> texel;
 
  texel.push_back(255); texel.push_back(0); texel.push_back(0);texel.push_back(255);
  texel.push_back(0); texel.push_back(255); texel.push_back(0);texel.push_back(255);
  texel.push_back(0); texel.push_back(0);texel.push_back(255);texel.push_back(255);
  texel.push_back(0); texel.push_back(255);texel.push_back(255);texel.push_back(255);
 
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glGenTextures(1,&texture_id);
    
  glBindTexture(GL_TEXTURE_2D,texture_id);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,&texel[0]);
  glDisable(GL_TEXTURE_2D);
}
 
 
 */
/*-------------------------------------------------------*/
void reshape(int w,int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0,5.0,-5.0,5.0,1.0,100.0);
  glMatrixMode(GL_MODELVIEW);
}
