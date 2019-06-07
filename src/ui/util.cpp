/***************************************************************************//**
* @file util.cpp
* @author Chezka Gaddi
* @brief Contains all functions manage event creations.
*******************************************************************************/
#include "util.h"


/***************************************************************************//**
* @author Chezka Gaddi
* @brief utilityCentral
*
* Creates the game manager and manages events to their associated functions
*******************************************************************************/
void utilityCentral(Event *event)
{
    static Game gameloop;

    event->doAction(gameloop);

    delete event;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief initOpenGL
*
* Initialize glut callback functions, set the display mode, create a window.
*
* @param[in] argc - number of command line arguments
* @param[in] argc - pointer to the list of command line arguments
* @param[in] wCols - width of the window
* @param[in] wRows - height of the window
* @param[in] mode - game mode
*******************************************************************************/
void initOpenGL(int argc, char** argv, int wCols, int wRows, Settings * setting)
{
    glutInit(&argc, argv);
        
    glutDisplayFunc(display);
    
    glutKeyboardFunc(keyboard);

    glutTimerFunc(750, ticktock, 750);

    glutCloseFunc(onClose);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
    
    glShadeModel(GL_SMOOTH);

    glutReshapeFunc(reshape);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    glutInitWindowSize(wCols, wRows);

    glutInitWindowPosition(10, 10);

    glutCreateWindow("Capture the Flag");

    glutSetIconTitle("images/icon.png");

    utilityCentral( new InitEvent(wCols, wRows, setting));
}
