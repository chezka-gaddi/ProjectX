/***************************************************************************//**
 * @file event.cpp
 * @author Chezka Gaddi
 * @brief Contains all of the maintenace functions for Event class and all of its
 * subclasses.
 ******************************************************************************/

#include "ui/event.h"
#include <iostream>
#include <memory>

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
InitEvent::InitEvent(int c, int r, Settings * s) : columns(c), rows(r), settings(s) {}


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
  game.initGameState(settings);
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
  std::unique_ptr<Drawable> temp_draw;
  std::unique_ptr<Projectile> temp_proj;
  std::unique_ptr<TankDrawable> temp_tank;
  unsigned int i = 0;

  if(!game.objects.empty())
    game.objects.clear();

  vector<ActorInfo> *actors = game.tankGame->getActorsPointer();
  vector<std::pair<int,int>> *SFX = game.tankGame->getSFXPointer();

  for(auto &act : *actors)
  {
    if(act.id > 0 && act.health > 0)
    {
      //Use smart pointers for better memory management
      std::unique_ptr<TankDrawable> temp_tank(new TankDrawable(act.id, game.convertGLXCoordinate(act.x), game.convertGLYCoordinate(act.y), act.heading, game.settings->getTurn(), game.settings->getModCounter(), act.offsetx, act.offsety, act.camp));
      act.sMod = !act.sMod;
      //Give our tanks health for sfx drawing
      temp_tank->setHealth(act.health);
      temp_tank->setMax_health(act.max_health);
      //move the smart pointer into the list
      game.objects.push_back(std::move(temp_tank));
    }
    else if(act.id < 0 && act.health > 0)
    {
      std::unique_ptr<Projectile> temp_proj(new Projectile(act.id, game.convertGLXCoordinate(act.x), game.convertGLYCoordinate(act.y), act.heading, (act.id == game.settings->getActTurn() || -act.id == game.settings->getActTurn()), act.offsetx, act.offsety, act.camp));
      temp_proj->sizeMod = act.scale;
      game.objects.push_back(std::move(temp_proj));
    }
    if(game.settings->getActTurn() == act.id)
    {
      for(i = 0; i < actors->size() && actors[0][i].id != game.settings->getActTurn(); i++);
      std::unique_ptr<Menu> temp_draw(new Menu(actors[0][i].id, actors[0][i].health, actors[0][i].ammo, actors[0][i].hits, actors[0][i].name, actors[0][i].heading, game.settings->getModCounter(), game.settings->getTurn()));
      game.objects.push_back(std::move(temp_draw));
    }

  }
  for(auto &sfx : *SFX)
  {
    std::unique_ptr<Drawable> temp_draw(new sfxDrawable(game.convertGLXCoordinate(sfx.first), game.convertGLYCoordinate(sfx.second)));
    game.sfx.push_back(std::move(temp_draw));
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  if (!game.settings->showUI()){
    return;
  }
  float pause;

  if(game.settings->getTurn() > 0)
    updateDrawables(game);

  for(unsigned int i = 0; i < game.constants.size(); i++)
  {
    game.constants[i]->draw(game.getX(), game.getY());
  }
  
  for(unsigned int i = 0; i < game.waters.size(); i++)
  {
    game.waters[i]->draw(game.getX(), game.getY());
  }

  for(unsigned int i = 0; i < game.specials.size(); i++)
  {
    if(game.specials[i]->health > 0)
      game.specials[i]->draw(game.getX(), game.getY());
  }

  for(unsigned int i = 0; i < game.objects.size(); i++)
  {
    game.objects[i]->draw(game.settings->getModCounter(), game.getY());
  }

  for(unsigned int i = 0; i < game.trees.size(); i++)
  {
    if(game.trees[i]->health > 0)
      game.trees[i]->draw(game.getX(), game.getY());
  }

  for(unsigned int i = 0; i < game.rocks.size(); i++)
  {
    if(game.rocks[i]->health > 0)
      game.rocks[i]->draw(game.getX(), game.getY());
  }
  for(unsigned int i = 0; i < game.bushes.size(); i++)
  {
    game.bushes[i]->draw(game.getX(), game.getY());
  }

  for(unsigned int i = 0; i < game.sfx.size(); i++)
  {
    game.sfx[i]->draw(game.getX(), game.getY());
  }
  game.sfx.clear();
  game.objects.clear();
  pause = TimerEvent::idle_speed*80;
  pause >= 0 ? usleep(pause) : usleep(0);
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
  if(TimerEvent::idle_speed != 0)
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
  idle_speed = game.settings->getIdleSpeed();
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
