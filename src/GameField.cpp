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
GameField::GameField(int width, int height)
{
  fieldMap.width = width;
  fieldMap.height = height;
  fieldMap.map.resize(width * height);
  fieldMap.obstacleMap.resize(width * height);
  settings = new Settings();
  std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
  std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
  displayCallback = NULL;
}
/**
 * @author David Donahue
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo
 */

GameField::GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>, int), Game * game, Settings * setting) : actors(startActors)
{
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
  settings = setting;
  actors = startActors;

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
void GameField::setSPECIAL(const attributes baseStats)
{
  int sum =0;
  int points = baseStats.tankSpecial;
  for(auto &actor: actors)
  {
    actor.tankAttributes = actor.act_p->setAttribute(points, baseStats);

    sum = actor.tankAttributes.tankHealth
          + actor.tankAttributes.tankAP
          + actor.tankAttributes.tankRadar
          + actor.tankAttributes.tankDamage
          + actor.tankAttributes.tankAmmo
          + actor.tankAttributes.projRange;
    if(sum  <= points)
    {
      actor.health += actor.tankAttributes.tankHealth;
      actor.AP += actor.tankAttributes.tankAP;
      actor.radar += actor.tankAttributes.tankRadar;
      actor.damage += actor.tankAttributes.tankDamage;
      actor.ammo += actor.tankAttributes.tankAmmo;
      actor.range += actor.tankAttributes.projRange;
      if(actor.health > 8)
      {
        actor.health = 8;
        printf("Health stat was too high,  clamping to 8.\n");
      }
      if(actor.AP > 6)
      {
        actor.AP = 6;
        printf("AP stat was too high, clamping to 6.\n");
      }
      if(actor.radar > getWidth())
      {
        actor.radar = getWidth();
        printf("Radar stat was too high, clamping to %d.\n", getWidth());
      }
      if(actor.damage > 8)
      {
        actor.damage = 8;
        printf("Damage stat was too high, clamping at 8.\n");
      }
      if(actor.ammo > 10)
      {
        actor.ammo = 10;
        printf("Ammo stat was too high, clamping at 10.\n");
      }
      if(actor.range > 10)
      {
        actor.range = 10;
        printf("Range stat was too high, clamping to 10.\n");
      }
    }
    else
      std::cout << "Tank "
                << actor.id
                << " did not provide the correct amount of special points! Points used: "
                << sum
                <<std::endl;

    actor.max_health = actor.health;
    actor.max_ammo = actor.ammo;
  }
}
/*********************************************************************//*
 * @author Jon McKee
 * @brief This function creates the animation effect for the object 
 * passed into it. The function works by checking the previous X and Y 
 * values of the actor and then continuously redrawing the object specified
 * by the number of samples in the animation speed game option.  Once the
 * draw is complete the object will be at it's new position with the new
 * location saved as the previous location for the next animation call.
 *
 * During this functions call the idletime is temporarily set to 0 and
 * reset back to the game setting at the end of the function.
 *
************************************************************************/ 
void GameField::animateMove(ActorInfo &a)
{
  if(((a.x == a.prevx) && (a.y == a.prevy)) || ((a.prevx == -1) || (a.prevy == -1))){  //We didn't actually move
    return;
  }
  int px = a.prevx;
  int py = a.prevy;
  int nx = a.x;
  int ny = a.y;
  int samples = 1; //If we're testing default to 1 sample
  GLfloat tempx, tempy;
  GLfloat prevx, prevy;
  if (gameptr != nullptr){//if we end up here while running catch tests, block out the invalid pointer (Other errors will occur)
    samples = settings->getAniFrames();
  
    if (a.id < 0)  //check if we need speed for a tank or projectile
      TimerEvent::idle_speed = settings->getBulletSpeed();
    else
      TimerEvent::idle_speed = settings->getTankSpeed();
  }
  switch(a.heading) //get our heading and loop through drawing samples
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
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
          displayCallback(fieldMap, actors, settings->getTurn());
      }
      break;

    default:
      //not sure what happened so don't move
      break;
  }
  a.offsety = 0; //Reset values 
  a.offsetx = 0;
  a.prevx = a.x; //Save new previous values
  a.prevy = a.y;
  if (gameptr != nullptr){//Skip during testing
   TimerEvent::idle_speed = settings->getIdleSpeed(); //fix idle speed
  }
}

/**
 * @author David Donahue
 * @author Jon McKee (Heavily Modified by)
 * @par Description:
 * Executes the move phase of an AI's turn and then AI's are culled
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
  if(a.health > 0 && hitObj == false && (xoff != 0 || yoff != 0))
  {
    if (a.id > 0){
      a.cDetect = 0;
      a.camp = false;
    }
    
    for(unsigned int i = 0; i < actors.size(); ++i)   //check each actor
    {
      if(a.id < 0 && actors[i].id == -a.id){
        a.camp = actors[i].camp;
      }
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
        else if(a.id < 0 && a.id != -actors[i].id)  //If we're a projectile and we hit a tank (Do not allow self hit)
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
  if (gameptr != nullptr){//Skip animating if we're not displaying the game
    if(!redraw && !hitObj){ //If we didn't hit an object and we don't need to force a redraw (Does not update map)
      animateMove(a);
    }
    if(hitObj || redraw){ //If either condition is true, animate 
      animateMove(a);
      updateMap(); //Update actors and map
      //printf("Currently %d number of explosions.\n",SFX.size());
      if (gameptr != nullptr) //redraw screen
        displayCallback(fieldMap, actors, settings->getTurn());
      SFX.clear(); //Clear the explosions
    } 
  }
  
}
/***********************************************************************//*
 * @author Jon McKee
 *
 * @brief Checks to see if the current object was killed or hit an object.
 * If the actor's health is less than or equal to 0 we 0 zero out its stats.
 * If the actor was a projectile and struck on object, we set it's health
 * equal to 0 and zero out the rest of it's stats.
 *
 *************************************************************************/
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

/****************************************************************************//*
 * @author Jon McKee
 * @brief Check to see if the current projectile hit an object.  If the curent
 * actor is not a projectile immediately.  If the current actor is a projectile
 * we check the various object lists to see if we struck one and then return the
 * appropriate flag.
 *
 ******************************************************************************/ 
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
          r->set_destroyed(settings->getTurn());
          removeObstacle(a.x, a.y);
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
          t->set_destroyed(settings->getTurn());
          removeObstacle(a.x, a.y);
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
        for (int i = gameptr->specials.size(); i > 0; i--){
                if (gameptr->specials[i-1]->health == 0){
                        removeObstacle(gameptr->specials[i-1]->gridx, gameptr->specials[i-1]->gridy);
                        gameptr->specials.erase(gameptr->specials.begin() + i - 1);
                }
        }
        return true;
      }
    }
  }
  return false;
}
/***************************************************************************//**
* @author Jon McKee
* @brief  Crate destruction.  We check every square in the range of the crate 
* and deal appropriate damage.  If we struck a crate we begin chaining our damage.
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
              if(t->health <= 0){
                t->destroyed = settings->getTurn();
                removeObstacle(t->gridx, t->gridy);
              }
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
              if(r->health <= 0){
                r->destroyed = settings->getTurn();
                removeObstacle(r->gridx, r->gridy);
                                }
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
            new_map.healthMap[value] = c->health;
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
          //Future use for destructible bushes
        /*case 'B':
          for(auto b : gameptr->bushes)
          {
            new_map.healthMap[value] = 1;
          }
          break;*/
      }
    }
  }
  map = new_map;

}
/**
 * @author David Donahue
 * @author Jon McKee (modified by)
 * @par Description:
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * Object regrowth is checked at the beginning of the turn phase.
 * AI's are culled at the end of the turn phase.
 */
void GameField::checkObjectRegrowth(){
  for(Obstacles* t : gameptr->trees)
  {
    if(t->health <= 0)
    {
      t->regrow(settings->getTurn(), actors);
      if (t->health > 0)
        addObstacle(t->gridx, t->gridy, 'T');
    }
  }
  for(Obstacles* r : gameptr->rocks)
  {
    if(r->health <= 0)
    {
      r->regrow(settings->getTurn(), actors);
      if (r->health > 0)
        addObstacle(r->gridx, r->gridy, 'R');
    }
  }
  //Currently bushes are non destructible but this will let them regrow when they do
  for(Obstacles* b : gameptr->bushes)
  {
    if(b->health <= 0)
    {
      b->regrow(settings->getTurn(), actors);
      if (b->health > 0)
        addObstacle(b->gridx, b->gridy, 'B');
    }
  }
}

/**
 * @author David Donahue
 * @author Jon McKee (modified by)
 * @par Description:
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * Object regrowth is checked at the beginning of the turn phase.
 * AI's are culled at the end of the turn phase.
 */

void GameField::nextTurn()
{
  if(settings != nullptr){
    settings->nextTurn();
  }

  direction atk;
  ActorInfo newProjectile;
  PositionData pos;
  int action;
  int act_ap;
  unsigned int j = 0;
  bool grow = false;
  MapData fog_of_war = fieldMap;
  if (gameptr != nullptr){
    checkObjectRegrowth();
  }
  for(unsigned int i = 0; i < actors.size(); ++i)
  {
    act_ap = actors[i].AP;
    if(actors[i].id > 0 && actors[i].health > 0 && gameptr != nullptr)
      settings->setActTurn(actors[i].id);
    updateMap();  //Give each actor a fresh map
    if(gameptr != nullptr)  
      displayCallback(fieldMap, actors, settings->getTurn());
    SFX.clear();
    while(act_ap > 0 && actors[i].id != 0 && actors[i].health > 0)
    {
      actors[i].cDetect++;
      if (gameptr != nullptr){
        settings->setModCounter(settings->getModCounter() + 1); 
        if(settings->getModCounter() > 7)
          settings->setModCounter(0);
      }
      updateMap();
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
            {//Check projectile list for a projectile in this spot
              if(actors[i].x == actors[j].x && actors[i].y == actors[j].y) //found one
              {
                actors[j].scale += .40;
                actors[j].health += 1;
                actors[j].ammo += 1;
                actors[j].damage += actors[i].damage;
                grow = true; //See if the projectile is one of our own
                break;
              }
              j++;
            }
            if(grow == false) //If there was no projectiles in this spot create a new one
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
          else if(atk != STAY)//Forced reload on empty ammo rack
          {
            //printf("Out of ammo... Out of ammo... Out of ammo... Reloading.  %d bullets left %d bullets fired.  ",actors[i].ammo,actors[i].shots);
            actors[i].ammo = actors[i].max_ammo;
            //printf("Back up to %d bullets.\n",actors[i].ammo);
          }
        }

      }
      else if(action == 4) //Chosen reload action
      {
        actors[i].ammo = actors[i].max_ammo;
        //printf("Reloading... Reloading... Reloading\n");
      }
      if (actors[i].health > 0 && actors[i].cDetect / actors[i].AP >= 4) //check for a camper
              actors[i].camp = true; //
      --act_ap;
    }
  }
  cull(); //Remove dead actors
  updateMap(); //update map
  if(gameptr != nullptr) //Draw map
    displayCallback(fieldMap, actors, settings->getTurn());
  SFX.clear(); //remove explosions that remain
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
    if(a.health + a.damage + a.AP + a.range > pointsAvailable)
    {
      a.health = 1;
      a.damage = 1;
      a.range = 1;
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
  for(unsigned int i = 0; i < actors.size(); ++i)  //This is used instead of the c++11 version so that we can use the index.
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
