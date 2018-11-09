/***************************************************************************//**
 * @file event.cpp
 * @author Chezka Gaddi
 * @brief Contains all of the maintenace functions for Event class and all of its
 * subclasses.
 ******************************************************************************/

#include "event.h"
#include <iostream>


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

    bool overlap = false;
    if(!game.objects.empty())
        game.objects.clear();

    vector <ActorInfo> actors = game.tankGame->getActors();
    vector <std::pair<int,int>> SFX = game.tankGame->getSFX();
    //for( auto obs : game.constants )
    //game.objects.push_back( obs );

    for( auto act : actors )
    {
        if( act.health > 0 && act.id > 0)
        {
            temp_draw = new TankDrawable( act.id, game.convertGLXCoordinate( act.x ), game.convertGLYCoordinate( act.y ), act.heading );
            game.objects.push_back( temp_draw );
            if (act.id <= 4)
            {
                temp_draw = new Menu( act.id, act.health, act.shots, act.hits );
                game.objects.push_back( temp_draw );
            }
        }

        else if( act.id < 0 && act.health > 0)
        {
            for(auto actor : actors)
            {
                if (actor.x == act.x && actor.y == act.y && actor.id != act.id && actor.health != 0)
                {
                    overlap = true;
                }
            }
            if(overlap != true)
            {
                temp_draw = new Projectile( act.id, game.convertGLXCoordinate( act.x ), game.convertGLYCoordinate( act.y), act.heading );
                game.objects.push_back(temp_draw);
            }
            overlap = false;
        }
    }
    overlap = false;
    for (auto sfx : SFX )
    {
        //printf("Adding explosion. At (%d,%d)\n", sfx.first, sfx.second);
        for (int i = 0; i < game.sfx.size(); i++)
        {
            if (game.sfx[i]->screen_x == game.convertGLXCoordinate(sfx.first)
                    && game.sfx[i]->screen_y == game.convertGLYCoordinate(sfx.second))
            {
                overlap = true;
                break;
            }
        }
        if (!overlap)
        {
            temp_draw = new sfxDrawable(game.convertGLXCoordinate( sfx.first ), game.convertGLYCoordinate(sfx.second));
            game.sfx.push_back(temp_draw);
        }
        overlap = false;
    }
    game.tankGame->clearSFX();
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
        stuff->draw(game.getX(), game.getY());
    }

    for( int i = 0; i < game.specials.size(); i++ )
    {
        stuff = game.specials[i];
        if (stuff->health > 0 )
            stuff->draw(game.getX(), game.getY());
    }

    for( int i = 0; i < game.objects.size(); i++ )
    {
        stuff = game.objects[i];
        stuff->draw(game.getX(), game.getY());
    }

    for( int i = 0; i < game.trees.size(); i++ )
    {
        stuff = game.trees[i];
        if (stuff->health > 0 )
            stuff->draw(game.getX(), game.getY());
    }

    for( int i = 0; i < game.rocks.size(); i++ )
    {
        stuff = game.rocks[i];
        if (stuff->health > 0 )
            stuff->draw(game.getX(), game.getY());
    }
    for( int i = 0; i < game.bushes.size(); i++ )
    {
        stuff = game.bushes[i];
        stuff->draw(game.getX(), game.getY());
    }
    for( int i = 0; i < game.sfx.size(); i++ )
    {
        stuff = game.sfx[i];
        stuff->draw(game.getX(), game.getY());
    }
    game.sfx.clear();
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
TimerEvent::TimerEvent(int &value)
{
    if (TimerEvent::idle_speed != 0)
        value = TimerEvent::idle_speed;
    tick = TimerEvent::idle_speed;
}


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
    idle_speed = game.getAISpeed();
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
