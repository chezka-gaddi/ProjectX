/***************************************************************************//**
 * @file event.cpp
 * @author Chezka Gaddi
 * @brief Contains all of the maintenace functions for Event class and all of its
 * subclasses.
 ******************************************************************************/

#include "event.h"


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief Destructor
 *
 * Destructor for Event class
 ******************************************************************************/
Event::~Event() {}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] c - columns (in pixels) of the window
 * @param[in] r - rows (in pixels) of the window
 ******************************************************************************/
InitEvent::InitEvent(int c, int r) : columns(c), rows(r) {}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief doAction
 *
 * Initializes the game state.
 *
 * @param[in] game - game manager
 ******************************************************************************/
void InitEvent::doAction(Game &game)
{
    glClear(GL_COLOR_BUFFER_BIT);
    game.initGameState();
}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief updateDrawables
 *
 * Remakes the objects vector to have the most current object coordinates.
 *
 * @param[in] game - game manager
 ******************************************************************************/
void updateDrawables(Game &game)
{
    Drawable *temp_draw = nullptr;

    if(!game.objects.empty())
        game.objects.clear();

    vector <ActorInfo> actors = game.tankGame->getActors();

    //for( auto obs : game.constants )
        //game.objects.push_back( obs );

    for( auto act : actors )
    {
        if( act.health > 0 && act.id > 0 )
        {
            temp_draw = new TankDrawable( act.id, game.convertGLXCoordinate( act.x ), game.convertGLYCoordinate( act.y ), act.heading );
            game.objects.push_back( temp_draw );
            temp_draw = new Menu( act.id, act.health, act.shots, act.hits );
            game.objects.push_back( temp_draw );
        }

        else if( act.id < 0 )
        {
            temp_draw = new Projectile( act.id, game.convertGLXCoordinate( act.x ), game.convertGLYCoordinate( act.y), act.heading );
            game.objects.push_back(temp_draw);
        }
    }
}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief doAction
 *
 * Draw all of the objects to the screen.
 *
 * @param[in] game - game manager
 ******************************************************************************/
void DisplayEvent::doAction(Game &game)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    
    updateDrawables(game);
    Drawable *stuff;


    for( int i = 0; i < game.constants.size(); i++ )
    {
        stuff = game.constants[i];
        stuff->draw();
    }
    
    
    for( int i = 0; i < game.objects.size(); i++ )
    {
        stuff = game.objects[i];
        stuff->draw();
    }

	
    system("sleep 0.2");
    glutSwapBuffers();
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] w - width (in pixels) of the window
 * @param[in] h - height (in pixels) of the window
 ******************************************************************************/
ReshapeEvent::ReshapeEvent(int w, int h) : width(w), height(h) {}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief doAction
 *
 * Re-adjust the view of the port when the window gets resized.
 *
 * @param[in] game - game manager
 ******************************************************************************/
void ReshapeEvent::doAction(Game &game)
{
    const float ar = width / height;
    glViewport(0, 10, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 90.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/***************************************************************************//**
 * @brief Constructor
 *
 * @param[in] tick - the number of milliseconds to wait before the next timer
 *    tick
 ******************************************************************************/
TimerEvent::TimerEvent(int value) : tick(value) {}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief doAction
 *
 * Waits until the timer to execute a turn so the movement of the objects can be
 * seen.
 *
 * @param[in] game - game manager
 ******************************************************************************/
void TimerEvent::doAction(Game &game)
{
    game.executeTurn();
}


/***************************************************************************//**
 * @brief Constructor
 ******************************************************************************/
CloseEvent::CloseEvent() {}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief doAction
 *
 * Calls the closeDown function when the window is exited.
 *
 * @param[in] game - game manager
 ******************************************************************************/
void CloseEvent::doAction(Game &game)
{
    game.closeDown();
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
    if(key == ESCAPE_KEY || key == 'Q' || key == 'q')
    {
        game.earlyOut();  
    }
}
