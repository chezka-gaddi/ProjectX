#include "util.h"

void utilityCentral(Event *event)
{
   static Game game;

   event->doAction(game);
   delete event;
}

/***************************************************************************//**
 * Initialize glut callback functions, set the display mode, create a window
 ******************************************************************************/
void initOpenGL(int argc, char** argv, int wCols, int wRows)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);

    glutInitWindowSize(wCols, wRows);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Capture the Flag");

    glutDisplayFunc(display);

    glEnable(GL_TEXTURE_2D);
    
    LoadGLTextures();
    
    glShadeModel(GL_SMOOTH);

    glutReshapeFunc(reshape);

    glutTimerFunc(1000, ticktock, 1000);

    glutCloseFunc(onClose);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClearDepth(1.0f);
    
    glEnable(GL_DEPTH_TEST);
    
    glDepthFunc(GL_LEQUAL);
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glDisable(GL_TEXTURE_2D);
    
    utilityCentral(new InitEvent(wCols, wRows));
}
