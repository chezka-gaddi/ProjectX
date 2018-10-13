/**
 * @file event.cpp
 * @brief Contains the functions of all events.
 * @author Chezka Gaddi
 **/

#include "event.h"


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


void updateDrawables(Game &game)
{
    cout << "\tREDRAWING\t\n";
    Drawable *temp_draw = nullptr;
    
    /*for( int i = 0; i < game.objects.size(); i++ )
    {
        Drawable *temp = game.objects.at(i);
        delete temp;
    }*/
   
    game.objects.clear();

    vector <ActorInfo> actors = game.tankGame->getActors();
    
    for( auto obs : game.obstacles )
        game.objects.push_back( obs );
    
    for( auto act : actors )
    {
        if( act.health > 0 && act.id > 0 )
        {
            temp_draw = new TankDrawable( act.id, game.convertGLXCoordinate( act.x ), game.convertGLYCoordinate( act.y) );
            game.objects.push_back( temp_draw );
        }

        else if( act.id < 0 )
        {
            temp_draw = new Projectile( act.id, game.convertGLXCoordinate( act.x ), game.convertGLYCoordinate( act.y) );
            game.objects.push_back(temp_draw);
        }
    }
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
    
    updateDrawables(game);    
    
    Drawable *stuff;
    
    for( int i = 0; i < game.objects.size(); i++ )  
    {
        stuff = game.objects[i];
        stuff->draw();
    }

    system("sleep 0.5");
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
