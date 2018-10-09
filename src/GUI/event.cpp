/**
 * @file event.cpp
 * @brief Contains the functions of all events.
 * @author Chezka Gaddi
 **/

#include "event.h"

GameField A;

Event::~Event() {}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] c - columns (in pixels) of the window
 * @param[in] r - rows (in pixels) of the window
 ******************************************************************************/
InitEvent::InitEvent(int c, int r) : columns(c), rows(r) {}

void InitEvent::doAction(Game &game)
{
   glClear(GL_COLOR_BUFFER_BIT);
   game.initGameState();
}


/**
 * @author Chezka Gaddi
 * @brief Draws the menu, player stats, gamefield, and tanks.
 * 
 * @param[in] game - game object
 **/
void DisplayEvent::doAction(Game &game)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    
    glEnable(GL_TEXTURE_2D);

    // Draw the gamefield
    A.updateTurn( game.turn );
    A.draw();

    // Draw the tanks
    for( auto tank : game.tanks )
        tank.draw();

    glDisable(GL_TEXTURE_2D);
    
	glutSwapBuffers();
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] w - width (in pixels) of the window
 * @param[in] h - height (in pixels) of the window
 ******************************************************************************/
ReshapeEvent::ReshapeEvent(int w, int h) : width(w), height(h) {}

void ReshapeEvent::doAction(Game &game)
{
    const float ar = width / height;
    glViewport(0, 10, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 90.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    std::cout << "Reshaping window to [" << width << ", " << height << "]\n";
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] b - the button that was pressed
 * @param[in] s - the state of the button that was pressed (0-down, 1-up)
 * @param[in] x - the x-coordinate of where the button 'b' was pressed/released
 * @param[in] y - the y-coordinate of where the button 'b' was pressed/released
 ******************************************************************************/
MouseClickEvent::MouseClickEvent(GLint b, GLint s, GLint x, GLint y) : 
   button(b), state(s), xLoc(x), yLoc(y) {}

void MouseClickEvent::doAction(Game &game) { }


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] x - the x-coordinate of where the button 'b' was pressed/released
 * @param[in] y - the y-coordinate of where the button 'b' was pressed/released
 ******************************************************************************/
MouseDragEvent::MouseDragEvent(int x, int y) : xLoc(x), yLoc(y) {}

void MouseDragEvent::doAction(Game &game) { }


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] x - the x-coordinate of where the button 'b' was pressed/released
 * @param[in] y - the y-coordinate of where the button 'b' was pressed/released
 ******************************************************************************/
MouseMoveEvent::MouseMoveEvent(int x, int y) : xLoc(x), yLoc(y) {}

void MouseMoveEvent::doAction(Game &game)
{
   stringstream ss;

   ss << "x = " << xLoc << " :: y = " << yLoc;
   glutSetWindowTitle(ss.str().c_str());
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] k - the ascii value of the key that was pressed
 * @param[in] x - the x-coordinate of where the key 'k' was pressed
 * @param[in] y - the y-coordinate of where the key 'k' was pressed
 ******************************************************************************/
KeyboardEvent::KeyboardEvent(unsigned char k, int x, int y) : key(k), xLoc(x), yLoc(y) {}

void KeyboardEvent::doAction(Game &game)
{
    if (key == ESCAPE_KEY)
        glutLeaveMainLoop();
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] k - the integer value of the key that was pressed
 * @param[in] x - the x-coordinate of where the key 'k' was pressed
 * @param[in] y - the y-coordinate of where the key 'k' was pressed
 ******************************************************************************/
SpecialKeyboardEvent::SpecialKeyboardEvent( int k, int x, int y) : key(k), xLoc(x), yLoc(y) {}


void SpecialKeyboardEvent::doAction(Game &game)
{
    int ID = 2;

    if( game.turn % 2 == 0 )
        ID = 1;
    
    switch (key) {
        case GLUT_KEY_RIGHT:
            for( int i = 0; i < game.tanks.size(); i++ )
            {
                if( game.tanks[i].tankID == ID )
                {
                    game.tanks[i].screen_x += 0.13;
                    game.tanks[i].angle = 0;
                }
            }

            game.executeTurn();
            break;

        case GLUT_KEY_LEFT:
            for( int i = 0; i < game.tanks.size(); i++ )
            {
                if( game.tanks[i].tankID == ID )
                {
                    game.tanks[i].screen_x -= 0.13;
                    game.tanks[i].angle = 180;
                }
            }

            game.executeTurn();
            break;
        
        case GLUT_KEY_UP:
            for( int i = 0; i < game.tanks.size(); i++ )
            {
                if( game.tanks[i].tankID == ID )
                {
                    game.tanks[i].screen_y += 0.09;
                    game.tanks[i].angle = 90;
                }
            }

            game.executeTurn();
            break;
        
        case GLUT_KEY_DOWN:
            for( int i = 0; i < game.tanks.size(); i++ )
            {
                if( game.tanks[i].tankID == ID )
                {
                    game.tanks[i].screen_y -= 0.09;
                    game.tanks[i].angle = -90;
                }
            }

            game.executeTurn();
            break;
    }
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] tick - the number of milliseconds to wait before the next timer
 *    tick
 ******************************************************************************/
TimerEvent::TimerEvent(int value) : tick(value) {}

void TimerEvent::doAction(Game &game)
{
   game.executeTurn();
}


/***************************************************************************//**
 * @brief Constructor
 ******************************************************************************/
CloseEvent::CloseEvent() {}

void CloseEvent::doAction(Game &game)
{
   game.closeDown();
}
