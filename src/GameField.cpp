/**
 * @file GameField.cpp
 * @author David Donahue
 */
#include "GameField.h"
#include "game.h"
#include <memory>
#include <iostream>
#include "event.h"

/**
 * @author David Donahue
 * @par Description:
 * Default constructor, makes a 10x10 empty map
 */

GameField::GameField() : ap(2)
{
  turnCount = 0;
  fieldMap.width = 10;
  fieldMap.height = 10;
  fieldMap.map.resize(100);
  fieldMap.obstacleMap.resize(100);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), 0);
  displayCallback = NULL;
}

/**
 * @author David Donahue
 * @par Description:
 * Destructor, deletes all actors left on the feild
 */

GameField::~GameField()
{
  for(auto &a : actors)
  {
    if(a.act_p != NULL)
      delete a.act_p;
  }
}

/**
 * @author David Donahue
 * @par Description:
 * Constructor given dimensions
 */
GameField::GameField(int width, int height) : ap(2)
{
  turnCount = 0;
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  displayCallback = NULL;
}
/**
 * @author David Donahue
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo
 */
GameField::GameField(int width, int height, std::vector<ActorInfo> acts) : actors(acts), ap(2)
{
  turnCount = 0;
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  updateMap();
  displayCallback = NULL;
}
/**
 * @author Riley Kopp
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo, and action points
 */
GameField::GameField(int width, int height, std::vector<ActorInfo> acts
, int actionpoints) : actors(acts), ap(actionpoints)
{
  turnCount = 0;
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  updateMap();
  displayCallback = NULL;
}

GameField::GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int)) : actors(startActors), ap(2)
{
  turnCount = 0;
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  updateMap();
  displayCallback = d_callback;
}

GameField::GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int), Game *game) : actors(startActors), ap(2)
{
  turnCount = 0;
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  x_scalar = 4.0717*pow(width, -1.031);
  y_scalar = 3.1923*pow(height, -1.08);
  updateMap();
  displayCallback = d_callback;
  gameptr = game;
}

GameField::GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int), int AP) : actors(startActors), ap(AP)
{
  turnCount = 0;
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  updateMap();
  displayCallback = d_callback;
}


/**
 * @author David Donahue
 * @par Description:
 * Gets the number of turns that have elapsed
 */
int GameField::getTurnCount()
{
  return turnCount;
}
/**
 * @author David Donahue
 * @par Description:
 * Gets the width of the field
 */
int GameField::getWidth()
{
  return fieldMap.width;
}
/**
 * @author David Donahue
 * @par Description:
 * Gets the height of the field
 */

int GameField::getHeight()
{
  return fieldMap.height;
}

/**
 * @author David Donahue
 * @par Description:
 * Gets just the map as a vector of ints
 */
std::vector<int> GameField::getMap()
{
  return fieldMap.map;
}
/**
 * @author David Donahue
 * @par Description:
 * Update the map with the current postions of all actors
 */
void GameField::updateMap()
{
  //erase the map
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  for(auto a : actors)
  {
    //for each actor fill in its id on the map
    if(a.health > 0)
      fieldMap.map[a.x+ fieldMap.width * a.y] = a.id;
  }

}
/***************************************************************************//**
 * @brief
 * Prompts the actors to choose attributes to specialize int
 * @author Riley Kopp
 ******************************************************************************/
void GameField::setSPECIAL(int points, const attributes baseStats)
{
  int sum =0;

  for(auto &actor: actors)
  {
    actor.tankAttributes = actor.act_p->setAttribute(points, baseStats);

    sum = actor.tankAttributes.tankHealth
          + actor.tankAttributes.tankAP
          + actor.tankAttributes.tankRadar
          + actor.tankAttributes.tankDamage
          + actor.tankAttributes.tankAmmo
          + actor.tankAttributes.tankRange;
    if(sum  <= points)
    {
      actor.health += actor.tankAttributes.tankHealth;
      actor.AP += actor.tankAttributes.tankAP;
      actor.radar += actor.tankAttributes.tankRadar;
      actor.damage += actor.tankAttributes.tankDamage;
      actor.ammo += actor.tankAttributes.tankAmmo;
      if(actor.health > 8)
      {
        actor.health = 8;
        printf("Health stat was too high, setting at 8.\n");
      }
      if(actor.AP > 8)
      {
        actor.AP = 8;
        printf("AP stat was too high, setting at 8.\n");
      }
      if(actor.radar > 16)
      {
        actor.radar = 16;
        printf("Radar stat was too high, setting at 16.\n");
      }
      if(actor.damage > 8)
      {
        actor.damage = 8;
        printf("Damage stat was too high, setting at 8.\n");
      }
      if(actor.ammo > 8)
      {
        actor.ammo = 8;
        printf("Ammo stat was too high, setting at 8.\n");
      }
    }
    else
      std::cout << "Tank "
                << actor.id
                << " did not provide the correct amount of special points! Points used: "
                << sum
                <<std::endl;
  }
}
void GameField::animateMove(ActorInfo &a)
{
  if(a.x == a.prevx && a.y == a.prevy || a.prevx == -1 || a.prevy == -1)  //We didn't actually move
    return;
  int px = a.prevx;
  int py = a.prevy;
  int nx = a.x;
  int ny = a.y;
  GLfloat tempx, tempy;
  GLfloat prevx, prevy;
  GLfloat newx, newy;
  int samples = gameptr->getAniSpeed();
#ifndef TESTING
  if (a.id < 0)
    TimerEvent::idle_speed = gameptr->getbullet_speed();
  else
    TimerEvent::idle_speed = gameptr->gettank_speed();
#endif
  switch(a.heading)
  {
    case UP:
      tempy = -1.75 - (ny * y_scalar); //smaller
      prevy = -1.75 - (py * y_scalar); //bigger
      tempy = (prevy - tempy); //-scaler
      tempy = tempy / samples; //scale it

      for(int i = 1; i < samples; i++)
      {
        a.offsety = tempy * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;
    case DOWN:
      tempy = -1.75 - (ny * y_scalar); //bigger
      prevy = -1.75 - (py * y_scalar); //smaller
      tempy = (prevy - tempy); //scaler
      tempy = tempy / samples; //scale it
      for(int i = 1; i < samples; i++)
      {
        a.offsety = tempy * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;

    case LEFT:
      tempx = .75 - (nx * x_scalar); //smaller
      prevx = .75 - (px * x_scalar); //bigger
      tempx = -(prevx - tempx); //-scaler
      tempx = tempx / samples; //scale it
      for(int i = 1; i < samples; i++)
      {
        a.offsetx = tempx * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;

    case RIGHT:
      tempx = .75 - (nx * x_scalar); //bigger
      prevx = .75 - (px * x_scalar); //smaller
      tempx = -(prevx - tempx); //scaler
      tempx = tempx / samples; //scale it
      for(int i = 1; i < samples; i++)
      {
        a.offsetx = tempx * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;
    case UPLEFT:
      tempy = -1.75 - (ny * y_scalar); //smaller
      prevy = -1.75 - (py * y_scalar); //bigger
      tempy = (prevy - tempy); //-scaler
      tempy = tempy / samples; //scale it
      tempx = .75 - (nx * x_scalar); //smaller
      prevx = .75 - (px * x_scalar); //bigger
      tempx = -(prevx - tempx); //-scaler
      tempx = tempx / samples; //scale it
      for(int i = 1; i <= samples; i++)
      {
        a.offsety = tempy * (samples - i);
        a.offsetx = tempx * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;

    case UPRIGHT:
      tempy = -1.75 - (ny * y_scalar); //smaller
      prevy = -1.75 - (py * y_scalar); //bigger
      tempy = (prevy - tempy); //-scaler
      tempy = tempy / samples; //scale it
      tempx = .75 - (nx * x_scalar); //bigger
      prevx = .75 - (px * x_scalar); //smaller
      tempx = -(prevx - tempx); //scaler
      tempx = tempx / samples; //scale it
      for(int i = 1; i <= samples; i++)
      {
        a.offsety = tempy * (samples - i);
        a.offsetx = tempx * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;

    case DOWNLEFT:
      tempy = -1.75 - (ny * y_scalar); //bigger
      prevy = -1.75 - (py * y_scalar); //smaller
      tempy = (prevy - tempy); //scaler
      tempy = tempy / samples; //scale it
      tempx = .75 - (nx * x_scalar); //smaller
      prevx = .75 - (px * x_scalar); //bigger
      tempx = -(prevx - tempx); //-scaler
      tempx = tempx / samples; //scale it
      for(int i = 1; i <= samples; i++)
      {
        a.offsety = tempy * (samples - i);
        a.offsetx = tempx * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;

    case DOWNRIGHT:
      tempy = -1.75 - (ny * y_scalar); //bigger
      prevy = -1.75 - (py * y_scalar); //smaller
      tempy = (prevy - tempy); //scaler
      tempy = tempy / samples; //scale it
      tempx = .75 - (nx * x_scalar); //bigger
      prevx = .75 - (px * x_scalar); //smaller
      tempx = -(prevx - tempx); //scaler
      tempx = tempx / samples; //scale it
      for(int i = 1; i <= samples; i++)
      {
        a.offsety = tempy * (samples - i);
        a.offsetx = tempx * (samples - i);
        if(gameptr != nullptr)
          displayCallback(fieldMap, actors, gameptr->turn);
      }
      break;

    default:
      //not sure what happened so don't move
      break;
  }
  a.offsety = 0;
  a.offsetx = 0;
  a.prevx = a.x;
  a.prevy = a.y;
#ifndef TESTING
  TimerEvent::idle_speed = gameptr->getAISpeed();
#endif
}

/**
 * @author David Donahue
 * @par Description:
 * Executes the move phase of an AI's turn
 * AI's are culled
 */
void GameField::runMoves(ActorInfo &a, MapData &fog, PositionData &pos)
{

  int xoff = 0, yoff = 0, tHealth = 0, hit = 0;
  bool hitObj = false;
  bool redraw = false;
  direction dir;

  //get the AI's desired move
  dir = a.act_p->move(fog, pos);
  a.heading = (dir == STAY) ? a.heading : dir; //Not the best move if we chose to stay
  //If it checks out, execute it
  //If the actor hits a wall or obstacle, do not execute the move and deal 1 damage
  if(a.health <= 0 || a.id == 0 || dir == STAY) //We arn't playing this game with dead actors anymore
    return;
  //store prev coordinates
  a.prevx = a.x;
  a.prevy = a.y;
  //try and move
  switch(dir)
  {
    case UP:
      if(a.y > 0 && (!obstacleAt(a.x, a.y - 1)
                     || obstacleAt(a.x, a.y - 1) == 'R'
                     || obstacleAt(a.x, a.y - 1) == 'T'
                     || obstacleAt(a.x, a.y - 1) == 'C'
                     || obstacleAt(a.x, a.y - 1) == 'B'
                     || obstacleAt(a.x, a.y - 1) == 'W'))
        yoff = -1;
      else
        a.health--;
      break;

    case DOWN:
      if(a.y < fieldMap.height-1 && (!obstacleAt(a.x, a.y + 1)
                                     || obstacleAt(a.x, a.y + 1) == 'R'
                                     || obstacleAt(a.x, a.y + 1) == 'T'
                                     || obstacleAt(a.x, a.y + 1) == 'C'
                                     || obstacleAt(a.x, a.y + 1) == 'B'
                                     || obstacleAt(a.x, a.y + 1) == 'W'))
        yoff = 1;
      else
        a.health--;
      break;

    case LEFT:
      if(a.x > 0 && (!obstacleAt(a.x - 1, a.y)
                     || obstacleAt(a.x - 1, a.y) == 'R'
                     || obstacleAt(a.x - 1, a.y) == 'T'
                     || obstacleAt(a.x - 1, a.y) == 'C'
                     || obstacleAt(a.x - 1, a.y) == 'B'
                     || obstacleAt(a.x - 1, a.y) == 'W'))
        xoff = -1;
      else
        a.health--;
      break;

    case RIGHT:
      if(a.x < fieldMap.width-1 && (!obstacleAt(a.x + 1, a.y)
                                    || obstacleAt(a.x + 1, a.y) == 'R'
                                    || obstacleAt(a.x + 1, a.y) == 'T'
                                    || obstacleAt(a.x + 1, a.y) == 'C'
                                    || obstacleAt(a.x + 1, a.y) == 'B'
                                    || obstacleAt(a.x + 1, a.y) == 'W'))
        xoff = 1;
      else
        a.health--;
      break;
    case UPLEFT:
      if(a.y > 0 && a.x > 0 && (!obstacleAt(a.x-1,a.y-1)
                                || obstacleAt(a.x-1,a.y-1)== 'R'
                                || obstacleAt(a.x-1,a.y-1)== 'T'
                                || obstacleAt(a.x-1,a.y-1)== 'C'
                                || obstacleAt(a.x-1,a.y-1) == 'B'
                                || obstacleAt(a.x-1,a.y-1) == 'W'))
      {
        yoff = -1;
        xoff = -1;
      }
      else
        a.health--;
      break;

    case UPRIGHT:
      if(a.y > 0 && a.x < fieldMap.width-1 && (!obstacleAt(a.x+1, a.y-1)
          || obstacleAt(a.x+1, a.y-1) == 'R'
          || obstacleAt(a.x+1, a.y-1) == 'T'
          || obstacleAt(a.x+1, a.y-1) == 'C'
          || obstacleAt(a.x+1, a.y-1) == 'B'
          || obstacleAt(a.x+1, a.y-1) == 'W'))
      {
        yoff = -1;
        xoff = 1;
      }
      else
        a.health--;
      break;

    case DOWNLEFT:
      if(a.y < fieldMap.height-1 && a.x > 0 && (!obstacleAt(a.x-1,a.y+1)
          || obstacleAt(a.x-1,a.y+1) == 'R'
          || obstacleAt(a.x-1,a.y+1) == 'T'
          || obstacleAt(a.x-1,a.y+1) == 'C'
          || obstacleAt(a.x-1,a.y+1) == 'B'
          || obstacleAt(a.x-1,a.y+1) == 'W'))
      {
        yoff = 1;
        xoff = -1;
      }
      else
        a.health--;
      break;

    case DOWNRIGHT:
      if(a.y < fieldMap.height-1 && a.x < fieldMap.width-1 && (!obstacleAt(a.x+1, a.y+1)
          || obstacleAt(a.x+1, a.y+1) == 'R'
          || obstacleAt(a.x+1, a.y+1) == 'T'
          || obstacleAt(a.x+1, a.y+1) == 'C'
          || obstacleAt(a.x+1, a.y+1) == 'B'
          || obstacleAt(a.x+1, a.y+1) == 'W'))
      {
        yoff = 1;
        xoff = 1;
      }
      else
        a.health--;
      break;

    default:
      break;
  }
  //Set our new positions
  a.x += xoff;
  a.y += yoff;
  hitObj = checkObjectStrike(a); //Check if our projectile hit a non-actor
  //Check if we're a tank that hit a rock or water
  if(a.id > 0 && (obstacleAt(a.x, a.y) == 'R' || obstacleAt(a.x, a.y) == 'W'))
  {
    a.x -= xoff;
    a.y -= yoff;
    hitObj = true;//Allows us to skip the rest of the checking if we ran into a rock or water
    redraw = true;//Allows us to skip animation
    a.health--;
  }

  //Run the main loop through actors to see if we hit one
  if(a.health > 0 && hitObj == false)
  {
    for(int i = 0; i < actors.size(); ++i)   //check each actor
    {
      if(a.health > 0 && actors[i].health > 0   //Make sure neither is dead
         && actors[i].x == a.x    //Make sure we're on the same column
         && actors[i].y == a.y    //Make sure we're on the same row
         && a.id != actors[i].id) //Make sure our tank doesn't damage itself
      {
        //Check tank to tank ramming
        if(a.id > 0 && actors[i].id > 0)
        {
          //printf("Tank hit tank\n");
          //Reverse the move
          a.x -= xoff;
          a.y -= yoff;
          //Store target tanks health
          tHealth = actors[i].health;
          actors[i].health -= a.health; //deal our full health damage to target
          //Logic for ramming
          if(a.health == 1)
          {
            hit += a.health; //tank kills self
          }
          else if(tHealth >= a.health)
          {
            hit += a.health - 1;//prevent tank's death (at least from ramming)
          }
          else //Otherwise take damage as normal
          {
            hit += tHealth; //Tank survives
          }
          a.hits++; //A tank hit is still a hit right?
          if(checkHealth(actors[i]))
            a.kills++;
          redraw = true; //This is the end of the road for this move, don't animate
        }
        else if(actors[i].id < 0)  //Check if we ran into a projectile (What we are doesn't matter)
        {
          //printf("Projectile or Tank hit a projectile.\n");
          hit += actors[i].damage; //store future damage
          actors[i].health = 0; //Destroy the projectile
          if(a.id > 0 && -actors[i].id != a.id){  //Give the owner a hit, but not a self hit and not a missile to missle hit
            actorInfoById(-actors[i].id).hits++;
            if (a.health -= hit <= 0) //Give the owner a kill if we suicided
                    actorInfoById(-actors[i].id != a.id);
          }
          redraw = true; //We hit something, don't animate more
        }
        else if(a.id < 0)  //If we're a projectile and we hit a tank
        {
          //printf("Projectile hit tank. %d hit %d\n",a.id,actors[i].id);
          actors[i].health -= a.damage; //damage the tank
          hit += a.health + 1; //should be enough to kill us
          if(a.id != -actors[i].id)       //no self hits which shouldn't be possible
            actorInfoById(-a.id).hits++;  //give our owner a hit
          if(checkHealth(actors[i]))
            actorInfoById(-a.id).kills++; //get a kill
          redraw = true;
        }
      }
    }
  }
  a.health -= hit;
  checkHealth(a, hitObj);
#ifndef TESTING
  if(!redraw && !hitObj){
    animateMove(a);
  }
  if(hitObj || redraw){
    animateMove(a);
    updateMap();
    //printf("Currently %d number of explosions.\n",SFX.size());
    if (gameptr != nullptr)
      displayCallback(fieldMap, actors, gameptr->turn);
    SFX.clear();
  }
#endif
  
}

bool GameField::checkHealth(ActorInfo &a, bool object)
{
  if(a.health <= 0) //if whatever we have has no health left
  {
    SFX.push_back(make_pair(a.x, a.y));
    a.damage = 0;
    a.id = 0;
    a.health = 0;
    a.AP = 0;
    return true;
  }
  else if(a.id < 0 && object) //If our projectile impacted on an object
  {
    SFX.push_back(make_pair(a.x, a.y));
    a.damage = 0;
    a.id = 0;
    a.health = 0;
    a.AP = 0;
    return true;
  }
  return false;
}

bool GameField::checkObjectStrike(ActorInfo &a)
{
  int tempOb = obstacleAt(a.x, a.y);
  int hits = 0;


  if(a.id > 0 || a.health < 0)  //Get the non projectiles back out of here
    return false;


  if(tempOb == 0)    //if the spot is empty then we couldn't have hit anything
  {
    //printf("Nothing hit at (%d, %d): %d Health: %d\n", a.x, a.y, tempOb, a.health);
    return false;
  }

  else if(tempOb == 'B' || tempOb == 'W')
  {
    //Bushes don't stop bullets
    //We technically dont need this now since bushes dont do anything, but we can make them destroyable later?
    //printf("Bush hit.  Not stopping.\n");
    return false;
  }
  else if(tempOb == 'R')
  {
    //printf("Rock strike, log it.\n");
    for(auto* r : gameptr->rocks)
    {
      if(r->gridx == a.x && r->gridy == a.y && r->health > 0)
      {
        //printf("Found Rock strike, log it.\n");
        r->health -= a.damage;
        SFX.push_back(make_pair(r->gridx, r->gridy));
        if(r->health <= 0)
        {
          r->health = 0;
#ifndef TESTING
          r->set_destroyed(gameptr->turn);
#endif
        }
        return true;
      }
    }
  }
  else if(tempOb == 'T')
  {
    for(auto* t : gameptr->trees)
    {
      if(t->gridx == a.x && t->gridy == a.y && t->health > 0)
      {
        //printf("Found tree strike, chop it.\n");
        t->health -= a.damage;
        SFX.push_back(make_pair(t->gridx, t->gridy));
        if(t->health <= 0)
        {
          t->health = 0;
#ifndef TESTING
          t->set_destroyed(gameptr->turn);
          //If a tree you're hiding under get's destroyed take 1 damage
          for (auto tTank : actors)
          {
                  if (tTank.x == a.x && tTank.y == a.y)
                          tTank.health--;
          }
#endif
        }
        return true;
      }
    }
  }
  else if(tempOb == 'C')
  {
    //printf("Hit the crate.\n");
    for(auto* &c : gameptr->specials)
    {
      if(c->gridx == a.x && c->gridy == a.y && c->health > 0)
      {
        // printf("Found the crate at (%d, %d) with projectile at (%d,%d).\n",c->gridx, c->gridy, a.x, a.y);
        c->health--;
        hits+= crate_o_doom(c->gridx, c->gridy, a);//Bang the drum
        actorInfoById(-a.id).hits += hits;
        return true;
      }
    }
  }
  return false;
}
/***************************************************************************//**
* @author Jon McKee
* @brief  Crate destruction
******************************************************************************/
bool  GameField::crate_o_doom(int x, int y, ActorInfo &a)
{
  //Steal the good parts from fog of war
  int radar = 1; //How big the explosion
  int x_pos = x;
  int y_pos = y;
  int x_max_radar_range = radar + x_pos >= fieldMap.width ? fieldMap.width - 1 : radar + x_pos;
  int y_max_radar_range = radar + y_pos >= fieldMap.height ? fieldMap.height - 1 : radar + y_pos;
  int y_min_radar_range = y_pos - radar < 0 ? 0 : y_pos - radar;
  int x_min_radar_range = x_pos - radar < 0 ? 0 : x_pos - radar;
  int hit = 0;

  for(int y_iter = y_min_radar_range; y_iter <= y_max_radar_range; y_iter++)
  {
    for(int x_iter = x_min_radar_range; x_iter <= x_max_radar_range; x_iter++)
    {
      switch(obstacleAt(x_iter, y_iter))  //now that we stole the internals do our stuff
      {
        case 'T':
          for(auto &t : gameptr->trees)
          {
            if(t->gridx == x_iter && t->gridy == y_iter && t->health > 0)
            {
              t->health--;
              if(t->health <= 0)
                t->destroyed = gameptr->turn;
            }
          }
          break;
        case 'C':
          for(auto &c : gameptr->specials)
          {
            if(c->gridx == x_iter && c->gridy == y_iter && c->health > 0)
            {
              c->health--;
              hit = crate_o_doom(c->gridx, c->gridy, a); //Chain reaction
            }
          }
          break;
        case 'R':
          for(auto &r : gameptr->rocks)
          {
            if(r->gridx == x_iter && r->gridy == y_iter && r->health > 0)
            {
              r->health--;
              if(r->health <= 0)
                r->destroyed = gameptr->turn;
            }
          }
          break;
        case 'B':
        default:
          for(auto &act : actors)
          {
            if(act.x == x_iter && act.y == y_iter && act.health > 0)
            {
              //printf("Hit a tank at (%d, %d)\n",x_iter, y_iter);
              act.health--;
              if(act.health <= 0)
              {
                act.health = 0;
                act.id = 0;
                actorInfoById(-a.id).kills++;
              }
              actorInfoById(-a.id).hits++;
            }
          }
          break;
      }
      SFX.push_back(make_pair(x_iter, y_iter));
    }
  }
  //printf("Hit %d number of tanks.\n",hit);
  return hit;

}
/***************************************************************************//**
* @author Riley Kopp
* @brief
* turns the map into just what the current tank can see based off radar
******************************************************************************/
void  GameField::create_fog_of_war(MapData &map, ActorInfo current_actor)
{

  if(current_actor.id <= 0)
    return;

  int radar = current_actor.radar;
  int x_pos = current_actor.x;
  int y_pos = current_actor.y;
  int x_max_radar_range = radar + x_pos >= map.width ? map.width - 1 : radar + x_pos;
  int y_max_radar_range = radar + y_pos >= map.height ? map.height - 1 : radar + y_pos;
  int y_min_radar_range = y_pos - radar < 0 ? 0 : y_pos - radar;
  int x_min_radar_range = x_pos - radar < 0 ? 0 : x_pos - radar;

  MapData new_map = map;
  std::fill(new_map.map.begin(), new_map.map.end(), 0);
  std::fill(new_map.obstacleMap.begin(), new_map.obstacleMap.end(), 0);
  new_map.healthMap.resize(new_map.width * new_map.height);
  std::fill(new_map.healthMap.begin(), new_map.healthMap.end(), 0);

  int value;
  for(int y_iter = y_min_radar_range; y_iter <= y_max_radar_range; y_iter++)
  {
    for(int x_iter = x_min_radar_range; x_iter <= x_max_radar_range; x_iter++)
    {
      value = y_iter * map.width + x_iter;
      new_map.map[value] = map.map[value];
      new_map.obstacleMap[value] = map.obstacleMap[value];
      if(map.obstacleMap[value] == 0 && map.map[value] != 0)
      {
        for(auto act : actors)
        {
          if(act.x == x_iter && act.y == y_iter && act.health > 0)
          {
            new_map.healthMap[value] = act.health;
          }
        }
      }
      switch(obstacleAt(x_iter, y_iter))
      {
        case 'T':
          for(auto t : gameptr->trees)
          {
            if(t->gridx == x_iter && t->gridy == y_iter && t->health > 0)
            {
              new_map.healthMap[value] = t->health;
            }
          }
          break;
        case 'C':
          for(auto c : gameptr->specials)
          {
            new_map.healthMap[value] = 1;
          }
          break;
        case 'R':
          for(auto r : gameptr->rocks)
          {
            if(r->gridx == x_iter && r->gridy == y_iter && r->health > 0)
            {
              new_map.healthMap[value] = r->health;
            }
          }
          break;
        case 'B':
          for(auto b : gameptr->bushes)
          {
            new_map.healthMap[value] = 1;
          }
          break;
      }
    }
  }
  map = new_map;

}
/**
 * @author David Donahue
 * @par Description:
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * AI's are culled
 */

void GameField::nextTurn()
{
  if(gameptr != nullptr)
    ++gameptr->turn;

  direction atk;
  ActorInfo newProjectile;
  PositionData pos;
  int action;
  int act_ap;
  int tSize, tId;
  int j = 0;
  bool grow = false;
  MapData fog_of_war = fieldMap;
  //printf("Turn number: %d\n",turnCount);
#ifndef TESTING  //Prevent testing from trying to access the unset pointer
  for(Obstacles* &t : gameptr->trees)
  {
    if(t->health <= 0)
    {
      t->regrow(gameptr->turn);
    }
  }
  for(Obstacles* &r : gameptr->rocks)
  {
    if(r->health <= 0)
    {
      r->regrow(gameptr->turn);
    }
  }
  for(Obstacles* &b : gameptr->bushes)
  {
    if(b->health <= 0)
    {
      b->regrow(gameptr->turn);
    }
  }
#endif
  for(int i = 0; i < actors.size(); ++i)
  {
    act_ap = actors[i].AP;
#ifndef TESTING //Prevent testing from trying to access the unset pointer
    if(actors[i].id > 0 && actors[i].health > 0)
      gameptr->actTurn = actors[i].id;
#endif
    updateMap();  //Give each actor a fresh map
    if(gameptr != nullptr)  
      displayCallback(fieldMap, actors, gameptr->turn);
    SFX.clear();
    while(act_ap > 0 && actors[i].id != 0 && actors[i].health > 0)
    {
#ifndef TESTING
      gameptr->modCounter++; 
      if(gameptr->modCounter > 7)
        gameptr->modCounter = 0;
#endif
      fog_of_war = fieldMap;
      create_fog_of_war(fog_of_war, actors[i]);
      pos.game_x = actors[i].x;
      pos.game_y = actors[i].y;
      pos.health = actors[i].health;
      pos.id = actors[i].id;
      pos.ap = act_ap;
      pos.ammo = actors[i].ammo;
      action = actors[i].act_p->spendAP(fog_of_war, pos);
      if(action == 1)
      {
        runMoves(actors[i], fog_of_war, pos);
      }

      else if(action == 2)
      {
        //PositionData to give the AI
        pos.game_x = actors[i].x;
        pos.game_y = actors[i].y;
        pos.health = actors[i].health;
        pos.id = actors[i].id;

        //Get the AI's desired attack
        atk = actors[i].act_p->attack(fog_of_war, pos);

        if(actors[i].id > 0)  //tanks attacking
        {
          if(atk != STAY && actors[i].ammo >= 1)
          {
            actors[i].heading = atk;
            j = i+1;
            grow = false;
            while(j < actors.size() && actors[i].id == -actors[j].id && actors[j].id < 0 && actors[j].health > 0)
            {
              if(actors[i].x == actors[j].x && actors[i].y == actors[j].y)
              {
                actors[j].scale += .40;
                actors[j].health += 1;
                actors[j].ammo += 1;
                actors[j].damage += actors[i].damage;
                grow = true;
                break;
              }
              j++;
            }
            if(grow == false)
            {
              ProjectileActor * proj = new ProjectileActor(atk);
              newProjectile.AP = actors[i].range;
              newProjectile.id = -actors[i].id;
              newProjectile.act_p = proj;
              newProjectile.health = 1;
              newProjectile.damage = actors[i].damage;
              newProjectile.x = actors[i].x;
              newProjectile.y = actors[i].y;
              newProjectile.hits = 0;
              newProjectile.ammo = 1;
              newProjectile.heading = actors[i].heading;
              actors.insert(actors.begin() + i + 1, newProjectile);
              actors[i].shots++;
              actors[i].ammo--;
            }
          }
          else if(atk != STAY)
          {
            //printf("Out of ammo... Out of ammo... Out of ammo... Reloading.  %d bullets left %d bullets fired.  ",actors[i].ammo,actors[i].shots);
            actors[i].ammo = actors[i].max_ammo;
            //printf("Back up to %d bullets.\n",actors[i].ammo);
          }
        }

      }
      else if(action == 4)
      {
        actors[i].ammo = actors[i].max_ammo;
        //printf("Reloading... Reloading... Reloading\n");
      }
      --act_ap;
    }
  }
  cull();
  updateMap();
  if(gameptr != nullptr)
    displayCallback(fieldMap, actors, gameptr->turn);
  SFX.clear();
}
/**
 * @author David Donahue
 * @par Description:
 * Add an actor to the list
 */
void GameField::addActor(ActorInfo a)
{
  actors.push_back(a);
  updateMap();
}

/**
 * @author Youki Lewis
 * @par Description:
 * Check if points are distributed properly
 */
void GameField::checkForCheaters(int pointsAvailable)
{
  for(auto &a : actors)
  {
    if(a.health + a.damage + a.AP + a.shots + a.range > pointsAvailable)
    {
      a.health = 1;
      a.damage = 1;
      a.range = 1;
      a.shots = 1;
      a.AP = 1;
    }
  }
}

/**
 * @author David Donahue
 * @par Description:
 * Adds an obstacle to the map
 *
 * @param[in] x - the x value of the obstacle
 * @param[in] y - the y value of the obstacle
 */

void GameField::addObstacle(int x, int y, int type)
{
  fieldMap.obstacleMap[x + fieldMap.width * y] = type;
}

/**
 * @author David Donahue
 * @par Description:
 * Removes an obstacle from the map
 *
 * @param[in] x - the x value of the obstacle
 * @param[in] y - the y value of the obstacle
 */

void GameField::removeObstacle(int x, int y)
{
  fieldMap.obstacleMap[x + fieldMap.width * y] = false;
}

/**
 * @author David Donahue
 * @par Description:
 * Get the current set of actors
 */
std::vector<ActorInfo> GameField::getActors()
{
  return actors;
}
/**
 * @author Jon McKee
 * @par Description:
 * Get a const version of the current set of actors
 */
std::vector<ActorInfo> *GameField::getActorsPointer()
{
  std::vector<ActorInfo> *temp;
  temp = &actors;
  return temp;
}
/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of actors
 */
const std::vector<ActorInfo> &GameField::getActorsConst()
{
  return actors;
}
/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of SFX
 */
std::vector<std::pair<int,int>> GameField::getSFX()
{
  return SFX;
}
/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of SFX
 */
std::vector<std::pair<int,int>> *GameField::getSFXPointer()
{
  std::vector<std::pair<int,int>> *temp;
  temp = &SFX;
  return temp;
}
/**
 * @author Jon McKee
 * @par Description:
 * Get the current set of SFX
 */
const std::vector<std::pair<int,int>> &GameField::getSFXConst()
{
  return SFX;
}
/**
 * @author Jon McKee
 * @par Description:
 * Clear the current set of SFX
 */
void GameField::clearSFX()
{
  SFX.clear();
}
/**
 * @author David Donahue
 * @par Description:
 * Get a vector of actors at a given location on the map
 */
std::vector<ActorInfo> GameField::findActorsByCoord(int x, int y)
{

  std::vector<ActorInfo> hits;
  for(auto a : actors)  //check each actor
  {
    if(a.x == x && a.y == y)
      hits.push_back(a);
  }
  return hits;

}
/**
 * @author David Donahue
 * @par Description:
 * Remove actors with hp of 0 from the game
 */
void GameField::cull()
{
  for(int i = 0; i < actors.size(); ++i)  //This is used instead of the c++11 version so that we can use the index.
  {
    if(actors[i].health == 0)
    {
      if(actors[i].name != "default\n")
      {
        //std::cout << "Tank Down!! " << actors[i].name << " died\n";
        deceased.push_back(actors[i]);
        //std::cout << "Current number of dead tanks is: " << deceased.size() << endl;
      }
      if(actors[i].act_p != NULL)
        delete actors[i].act_p;
      actors.erase(actors.begin()+i);
      --i; // go back one since everything just shifted back
    }
  }

}
/**
 * @author David Donahue
 * @par Description:
 * Returns the full fieldMap as a MapData struct
 */
MapData GameField::getMapData()

{
  return fieldMap;
}

/**
 * @author David Donahue
 * @par Description:
 * Finds an actor by its ID and returns a reference to it
 *
 * @param[in] id - the ID of the actor
 * @return Reference to the desired actor or a reference to a 'null' actor
 *
 */

ActorInfo & GameField::actorInfoById(int id)
{
  for(auto &a : actors)
  {
    if(a.id == id)
      return a;
  }
  return nullActor;
}



/**
 * @author David Donahue
 * @par Description:
 * Determines whether a space has an obstacle on it
 *
 * @param[in] x - the X coordinate of the tile
 * @param[in] y - the Y coordinate of the tile
 * @return true if an obstacle exists at a tile, false if not
 *
 */
int GameField::obstacleAt(int x, int y)
{
  return fieldMap.obstacleMap[x + y * fieldMap.width];

}

std::string GameField::getWinner()
{
  string winner = "none";
  for(auto a : actors)
    if(a.health > 0 && a.id > 0)
      winner = a.name;
  return winner;
}
