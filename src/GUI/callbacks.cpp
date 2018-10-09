/***************************************************************************//**
 * @file callbacks.cpp
 ******************************************************************************/
#include "callbacks.h"

// OpenGL thinks the y = 0 coordinate is at the top of the screen.  Flip it over
int actualY(int y)
{
   return glutGet(GLUT_WINDOW_HEIGHT) - y;
}

/***************************************************************************//**
 * @brief A callback function for refreshing the display
 ******************************************************************************/
void display() 
{
   utilityCentral(new DisplayEvent());
}

/***************************************************************************//**
 * @brief A callback function for handling keyboard input
 *
 * @param[in] key - the key that was pressed
 * @param[in] x   - the x-coordinate when the key was pressed
 * @param[in] y   - the y-coordinate when the key was pressed
 ******************************************************************************/
void keyboard(unsigned char key, int x, int y)
{
   //utilityCentral(new KeyboardEvent(key, x, actualY(y)));
   utilityCentral(new KeyboardEvent(key, x, y));
}

void specialKeyboard(int key, int x, int y)
{
   //utilityCentral(new KeyboardEvent(key, x, actualY(y)));
   utilityCentral(new SpecialKeyboardEvent(key, x, y));
}
/***************************************************************************//**
 * @brief A callback function for handling mouse click events
 *
 * @param[in] button - the mouse button pushed
 * @param[in] state  - the state of the button (i.e. GLUT_UP, GLUT_DOWN)
 * @param[in] x      - the x-coordinate when the button is pressed
 * @param[in] y      - the y-coordinate when the button is pressed
 ******************************************************************************/
void mouseClick(GLint button, GLint state, GLint x, GLint y)
{
   //utilityCentral(new MouseClickEvent(button, state, x, actualY(y)));
   utilityCentral(new MouseClickEvent(button, state, x, y));
}

/***************************************************************************//**
 * @brief A callback function for handling mouse drag events
 *
 * @param[in] x      - current x-coordinate while the button is pressed
 * @param[in] y      - current y-coordinate while the button is pressed
 ******************************************************************************/
void mouseDrag(int x, int y)
{
   utilityCentral(new MouseDragEvent(x, actualY(y)));
}

/***************************************************************************//**
 * @brief A callback function for handling mouse move events
 *
 * @param[in] x      - current x-coordinate while the button is not pressed
 * @param[in] y      - current y-coordinate while the button is not pressed
 ******************************************************************************/
void mouseMove(int x, int y)
{
   utilityCentral(new MouseMoveEvent(x, actualY(y)));
}

/***************************************************************************//**
 * @brief A callback function for handling window resize events
 *
 * @param[in] w      - new window width
 * @param[in] h      - new window height
 ******************************************************************************/
void reshape(const int w, const int h)
{
    glLoadIdentity();
    // project 3d world space into 2d
    gluOrtho2D(0.0, w, 0.0, h);
    // point the camera at the 2d projection
    glViewport(0,0,w,h);
    // dispatch the reshape event
    utilityCentral(new ReshapeEvent(w, h));
}

/***************************************************************************//**
 * @brief A callback function for handling timer events
 *
 * @param[in] value  - The elapsed time (in milliseconds) since the last
 *                     timer event
 ******************************************************************************/
void ticktock(int value)
{
   // Dispatch the timer event to the central control function
   utilityCentral(new TimerEvent(value));
   // Set the next timer event elapsed time and function to call
   glutTimerFunc(value, ticktock, value);
}

void onClose()
{
   utilityCentral(new CloseEvent());
}
