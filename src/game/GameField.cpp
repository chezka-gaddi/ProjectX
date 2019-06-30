/**
 * @file GameField.cpp
 * @author David Donahue
 */

#include <memory>
#include <iostream>
#include "ui/event.h"
#include "game/GameField.h"
#include "game/game.h"

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
  if (settings->checkTracking())
    tracker->close();
}

/**
 * @author David Donahue
 * @par Description:
 * Constructor given dimensions
 */ 
GameField::GameField(int width, int height)
{
  fieldMap = new MapData(width, height);
  settings = new Settings();
  fieldMap->generateTileMap();
  displayCallback = NULL;
  if (settings->checkTracking()){
    tracker = new gameTracker();
    tracker->open();
  }
}
/**
 * @author David Donahue
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo
 */

GameField::GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(Settings *) = NULL, Game * game = nullptr, Settings * setting = nullptr) : actors(startActors)
{
  fieldMap = new MapData(width, height);
  x_scalar = 4.0717 * pow(width, -1.031);
  y_scalar = 3.1923 * pow(height, -1.08);
  //updateMap();
  displayCallback = d_callback;
  gameptr = game;
  if (setting == nullptr){
    settings = new Settings();
  }else{
    settings = setting;
  }
  actors = startActors;
  if (settings->checkTracking()){
    tracker = new gameTracker();
    tracker->open();
  }
}

/**
 * @author David Donahue
 * @par Description:
 * Gets the width of the field
 */
int GameField::getWidth()
{
  return fieldMap->width;
}
/**
 * @author David Donahue
 * @par Description:
 * Gets the height of the field
 */

int GameField::getHeight()
{
  return fieldMap->height;
}

/**
 * @author David Donahue
 * @modifiedby Jon McKee
 * @par Description:
 * Update the map with the current postions of all actors
 */
void GameField::updateMap()
{
  //Add each actor back to map or update it's health
  for(auto a : actors)
  {
    //for each actor fill in its id on the map
    if(a.health > 0){
      if (a.id > 0){
        if (fieldMap->tileMap[a.y][a.x].actor == nullptr){
          fieldMap->tileMap[a.y][a.x].actor = new Tile("Tank", a.id, a.x, a.y, a.health, nullptr, nullptr);
        }else{
          fieldMap->tileMap[a.y][a.x].actor->x = a.x;
          fieldMap->tileMap[a.y][a.x].actor->y = a.y;
          fieldMap->tileMap[a.y][a.x].actor->health = a.health;
        }
      }else{
        if (fieldMap->tileMap[a.y][a.x].projectile == nullptr){
          fieldMap->tileMap[a.y][a.x].projectile = new Tile("Projectile", a.id, a.x, a.y, a.health, nullptr, nullptr);
        }else{
          fieldMap->tileMap[a.y][a.x].projectile->x = a.x;
          fieldMap->tileMap[a.y][a.x].projectile->y = a.y;
          fieldMap->tileMap[a.y][a.x].projectile->health = a.health;
        }
      }
    }
  }
  if (gameptr != nullptr){
    for(auto * t : gameptr->trees)
    {
      if (t->health > 0){
        fieldMap->tileMap[t->gridy][t->gridx].health = t->health;
      }
    }
    for(auto * r : gameptr->rocks)
    {
      if (r->health > 0){
        fieldMap->tileMap[r->gridy][r->gridx].health = r->health;
      }
    }
    for(auto * b : gameptr->bushes)
    {
      if (b->health > 0){
        fieldMap->tileMap[b->gridy][b->gridx].health = b->health;
      }
    }
  }
}
/***************************************************************************//**
 * @brief
 * Prompts the actors to choose attributes to specialize int
 * @author Riley Kopp
 * @modifiedby Jon McKee
 ******************************************************************************/
void GameField::setSPECIAL(const attributes baseStats)
{
  int sum = 0;
  int points = baseStats.tankSpecial;
  attributes tempAttr;
  for(auto &actor: actors)
  {
    tempAttr = actor.act_p->setAttribute(points, baseStats);
    
    if (tempAttr.tankHealth < 0){
      tempAttr.tankHealth = 0;
      printf("(SPECIAL-Spend AP) %s Negative health point value, setting to 0.\n", actor.name.c_str());
    }
    if (tempAttr.tankAP < 0){
      tempAttr.tankAP = 0;
      printf("(SPECIAL-Spend AP) %s Negative health point value, setting to 0.\n", actor.name.c_str());
    }
    if (tempAttr.tankRadar < 0){
      tempAttr.tankRadar = 0;
      printf("(SPECIAL-Spend AP) %s Negative health point value, setting to 0.\n", actor.name.c_str());
    }
    if (tempAttr.tankDamage <0){
      tempAttr.tankDamage = 0;
      printf("(SPECIAL-Spend AP) %s Negative health point value, setting to 0.\n", actor.name.c_str());
    }
    if (tempAttr.tankAmmo < 0){
      tempAttr.tankAmmo = 0;
      printf("(SPECIAL-Spend AP) %s Negative health point value, setting to 0.\n", actor.name.c_str());
    }
    if (tempAttr.projRange < 0){
      tempAttr.projRange = 0;
      printf("(SPECIAL-Spend AP) %s Negative health point value, setting to 0.\n", actor.name.c_str());
    }

    sum = tempAttr.tankHealth
          + tempAttr.tankAP
          + tempAttr.tankRadar
          + tempAttr.tankDamage
          + tempAttr.tankAmmo
          + tempAttr.projRange;
    if(sum <= points)
    {
      actor.health += tempAttr.tankHealth;
      actor.AP += tempAttr.tankAP;
      actor.radar += tempAttr.tankRadar;
      actor.damage += tempAttr.tankDamage;
      actor.ammo += tempAttr.tankAmmo;
      actor.range += tempAttr.projRange;
      if(actor.health > 8)
      {
        actor.health = 8;
        printf("%s: Health stat was too high,  clamping to 8.\n", actor.name.c_str());
      }
      if(actor.AP > 6)
      {
        actor.AP = 6;
        printf("%s: AP stat was too high, clamping to 6.\n", actor.name.c_str());
      }
      if(actor.radar > getWidth())
      {
        actor.radar = getWidth();
        printf("%s: Radar stat was too high, clamping to %d.\n", actor.name.c_str(), getWidth());
      }
      if(actor.damage > 8)
      {
        actor.damage = 8;
        printf("%s: Damage stat was too high, clamping at 8.\n", actor.name.c_str());
      }
      if(actor.ammo > 10)
      {
        actor.ammo = 10;
        printf("%s: Ammo stat was too high, clamping at 10.\n", actor.name.c_str());
      }
      if(actor.range > 10)
      {
        actor.range = 10;
        printf("%s: Range stat was too high, clamping to 10.\n", actor.name.c_str());
      }
    }
    else
      std::cout << "Tank "
                << actor.id
                << "(" << actor.name.c_str() << ")"
                << " did not provide the correct amount of special points! Points used: "
                << sum
                << std::endl;

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
  int px = a.prevx, py = a.prevy, nx = a.x, ny = a.y;
  int samples = 1; //If we're testing default to 1 sample
  GLfloat tempx, tempy;
  if (gameptr != nullptr){//if we end up here while running catch tests, block out the invalid pointer (Other errors will occur)
    samples = settings->getAniFrames();
  
    if (a.id < 0)  //check if we need speed for a tank or projectile
      TimerEvent::idle_speed = settings->getBulletSpeed();
    else
      TimerEvent::idle_speed = settings->getTankSpeed();
  }
  tempy = ((-1.75 - (py * y_scalar)) - (-1.75 - (ny * y_scalar))) / samples;
  tempx = -((.75 - (px * x_scalar)) - (.75 - (nx * x_scalar))) / samples;

  //Only need to adjust for single values
  if (a.heading == UP || a.heading == DOWN)
    tempx = 0;
  if (a.heading == LEFT || a.heading == RIGHT)
    tempy = 0;

  for(int i = 1; i <= samples; i++)
  {
    a.offsety = tempy * (samples - i);
    a.offsetx = tempx * (samples - i);
    if(gameptr != nullptr)
      displayCallback(settings);
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
  direction dir;
  Tile * tempObj;

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
      if(a.y > 1 && (obstacleAt(a.x, a.y - 1) != 1))
        yoff = -1;
      else
        a.health--;
      break;

    case DOWN:
      if(a.y < fieldMap->height && (obstacleAt(a.x, a.y + 1) != 1))
        yoff = 1;
      else
        a.health--;
      break;

    case LEFT:
      if(a.x > 1 && (obstacleAt(a.x - 1, a.y) != 1))
        xoff = -1;
      else
        a.health--;
      break;

    case RIGHT:
      if(a.x < fieldMap->width && (obstacleAt(a.x + 1, a.y) != 1))
        xoff = 1;
      else
        a.health--;
      break;

    case UPLEFT:
      if(a.y > 1 && a.x > 1 && (obstacleAt(a.x-1,a.y-1) != 1))
      {
        yoff = -1;
        xoff = -1;
      }
      else
        a.health--;
      break;

    case UPRIGHT:
      if(a.y > 1 && a.x < fieldMap->width && (obstacleAt(a.x+1, a.y-1) != 1))
      {
        yoff = -1;
        xoff = 1;
      }
      else
        a.health--;
      break;

    case DOWNLEFT:
      if(a.y < fieldMap->height && a.x > 1 && (obstacleAt(a.x-1,a.y+1) != 1))
      {
        yoff = 1;
        xoff = -1;
      }
      else
        a.health--;
      break;

    case DOWNRIGHT:
      if(a.y < fieldMap->height && a.x < fieldMap->width && (obstacleAt(a.x+1, a.y+1) != 1))
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
  
  if (a.id > 0){
    delete fieldMap->tileMap[a.y][a.x].actor;
    fieldMap->tileMap[a.y][a.x].actor = nullptr;
  }else{
    delete fieldMap->tileMap[a.y][a.x].projectile;
    fieldMap->tileMap[a.y][a.x].projectile = nullptr;
  }
  
  a.x += xoff;
  a.y += yoff;
  tempObj = &fieldMap->tileMap[a.y][a.x];
  hitObj = checkObjectStrike(a); //Check if our projectile hit a non-actor
  //Check if we're a tank that hit a rock or water
  if(a.id > 0 && (tempObj->type == "Rock" || tempObj->type == "Water"))
  {
    a.x -= xoff;
    a.y -= yoff;
    hitObj = true;//Allows us to skip the rest of the checking if we ran into a rock or water
    a.health--;
  }

  //Run the main loop through actors to see if we hit one
  if(a.health > 0 && hitObj == false && (xoff != 0 || yoff != 0))
  {
    if (a.id > 0){
      a.cDetect = 0;
      a.camp = false;
    }
    if (tempObj->actor != nullptr){ //Only check for actors if there was one in the tile
      for(unsigned int i = 0; i < actors.size(); ++i)   //check each actor
      {
        if(a.id < 0 && actors[i].id == -a.id){//If it's one of our projectiles update it's camp value
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
          }
        }
      }
    }
  }
  a.health -= hit;
  checkHealth(a, hitObj);
  if (gameptr != nullptr){//Skip animating if we're not displaying the game
    animateMove(a);
    updateMap(); //Update actors and map
    //printf("Currently %d number of explosions.\n",SFX.size());
    displayCallback(settings);
    SFX.clear(); //Clear the explosions
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
          r->set_destroyed(gameTurn);
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
          t->set_destroyed(gameTurn);
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
        hits += crate_o_doom(c->gridx, c->gridy, a);//Bang the drum
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
  int x_max_radar_range = radar + x_pos > fieldMap->width ? fieldMap->width : radar + x_pos;
  int y_max_radar_range = radar + y_pos > fieldMap->height ? fieldMap->height : radar + y_pos;
  int y_min_radar_range = y_pos - radar < 1 ? 1 : y_pos - radar;
  int x_min_radar_range = x_pos - radar < 1 ? 1 : x_pos - radar;
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
                t->destroyed = gameTurn;
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
                r->destroyed = gameTurn;
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
MapData * GameField::create_fog_of_war(const MapData &map, ActorInfo current_actor)
{
  MapData * new_map = new MapData(map.width, map.height);

  if(current_actor.id <= 0)
    return new_map;

  int radar = current_actor.radar;
  int x_pos = current_actor.x;
  int y_pos = current_actor.y;
  int x_max_radar_range = radar + x_pos > map.width ? map.width : radar + x_pos;
  int y_max_radar_range = radar + y_pos > map.height ? map.height : radar + y_pos;
  int y_min_radar_range = y_pos - radar < 1 ? 1 : y_pos - radar;
  int x_min_radar_range = x_pos - radar < 1 ? 1 : x_pos - radar;

  //int value;
  for(int y_iter = y_min_radar_range; y_iter <= y_max_radar_range; y_iter++)
  {
    for(int x_iter = x_min_radar_range; x_iter <= x_max_radar_range; x_iter++)
    {
      new_map->tileMap[y_iter][x_iter] = map.tileMap[y_iter][x_iter];
      if (map.tileMap[y_iter][x_iter].type != "Empty" && map.tileMap[y_iter][x_iter].health <= 0){//Don't send hidden data on objects that have been destroyed
        new_map->tileMap[y_iter][x_iter].type = "Empty";
        new_map->tileMap[y_iter][x_iter].health = 0;
      }
    }
  }
  return new_map;
}

/**
 * @author Jon McKee
 * @par Description:
 * This function checks all objects to see if they should be regrown
 */
void GameField::checkObjectRegrowth(){
  for(Obstacles* t : gameptr->trees)
  {
    if(t->health <= 0)
    {
      t->regrow(gameTurn, actors);
      if (t->health > 0)
        addObstacle(t->gridx, t->gridy, 'T');
    }
  }
  //Rocks don't regrow
  //for(Obstacles* r : gameptr->rocks)
  //{
  //  if(r->health <= 0)
  //  {
  //    r->regrow(gameTurn, actors);
  //    if (r->health > 0)
  //      addObstacle(r->gridx, r->gridy, 'R');
  //  }
  //}
  //Currently bushes are non destructible but this will let them regrow when they do
  for(Obstacles* b : gameptr->bushes)
  {
    if(b->health <= 0)
    {
      b->regrow(gameTurn, actors);
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
  gameTurn++;
  //Debug tileMap updating
  //if (gameTurn >= 1){
  //  printf("Game turn: %d\n", gameTurn);
  //  fieldMap->printTileMap();
  //}
  if (tracker != nullptr)
    tracker->newTurn(gameTurn);
  direction atk;
  ActorInfo newProjectile;
  PositionData pos;
  MapData * fog_of_war;
  int action;
  int act_ap;
  unsigned int j = 0;
  bool grow = false;
  if (gameptr != nullptr){
    checkObjectRegrowth();
  }
  for(unsigned int i = 0; i < actors.size(); ++i)
  {
    act_ap = actors[i].AP;
    if(actors[i].id > 0 && actors[i].health > 0){
      actTurn = actors[i].id;
    }
    if (tracker != nullptr)
        tracker->newPlayerTurn(actors[i].id);
    
    updateMap();  //Give each actor a fresh map
    if(gameptr != nullptr && settings->showUI())  
      displayCallback(settings);
    SFX.clear();
    while(act_ap > 0 && actors[i].id != 0 && actors[i].health > 0)
    {
      actors[i].cDetect++;
      modCounter++;
      if(modCounter > 7)
        modCounter = 0;
      updateMap();
      fog_of_war = create_fog_of_war(*fieldMap, actors[i]);
      pos.game_x = actors[i].x;
      pos.game_y = actors[i].y;
      pos.health = actors[i].health;
      pos.id = actors[i].id;
      pos.ap = act_ap;
      pos.ammo = actors[i].ammo;
      action = actors[i].act_p->spendAP(*fog_of_war, pos);
      if(action == 1)
      {
        runMoves(actors[i], *fog_of_war, pos);
        if (tracker != nullptr && actors[i].id > 0){
          tracker->move(actors[i].name, actors[i].heading, actors[i].x, actors[i].y);
        }else if (tracker != nullptr){
          tracker->move("Projectile", actors[i].heading, actors[i].x, actors[i].y);
        }
      }
      else if(action == 2)
      {
        //PositionData to give the AI
        pos.game_x = actors[i].x;
        pos.game_y = actors[i].y;
        pos.health = actors[i].health;
        pos.id = actors[i].id;

        //Get the AI's desired attack
        atk = actors[i].act_p->attack(*fog_of_war, pos);
    
        if(actors[i].id > 0)  //tanks attacking
        {
          if (tracker != nullptr){
            tracker->attack(actors[i].name, atk);
          }
          if(atk != STAY && actors[i].ammo >= 1)
          {
            actors[i].heading = atk;
            actors[i].shots += 1;
            j = i+1;
            grow = false;
            if (fieldMap->tileMap[actors[i].y][actors[i].x].projectile != nullptr){ //If no projectile we don't need to check the list
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
              newProjectile.name = "Projectile\n";
              actors.insert(actors.begin() + i + 1, newProjectile);
              actors[i].ammo--;
              fieldMap->tileMap[actors[i].y][actors[i].x].projectile = new Tile("Projectile", newProjectile.id, newProjectile.x, newProjectile.y, newProjectile.health, nullptr, nullptr);
            }
          }
          else if(atk != STAY)//Forced reload on empty ammo rack
          {
            if (tracker != nullptr){
              tracker->reload(actors[i].name, true);
            }
            //printf("Out of ammo... Out of ammo... Out of ammo... Reloading.  %d bullets left %d bullets fired.  ",actors[i].ammo,actors[i].shots);
            actors[i].ammo = actors[i].max_ammo;
            //printf("Back up to %d bullets.\n",actors[i].ammo);
          }
        }
      }
      else if(action == 4) //Chosen reload action
      {
        if (tracker != nullptr){
          tracker->reload(actors[i].name, false);
        }
        actors[i].ammo = actors[i].max_ammo;
        //printf("Reloading... Reloading... Reloading\n");
      }
      if (actors[i].health > 0 && actors[i].cDetect / actors[i].AP >= 4){ //check for a camper
        actors[i].camp = true; //
        if (tracker != nullptr){
          tracker->camp(actors[i].name);
        }
      
      }
      delete fog_of_war;
      --act_ap;
    }
  }
  cull(); //Remove dead actors
  updateMap(); //update map
  if(gameptr != nullptr && settings->showUI()) //Draw map
    displayCallback(settings);
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
 * @author David Donahue
 * @par Description:
 * Adds an obstacle to the map
 *
 * @param[in] x - the x value of the obstacle
 * @param[in] y - the y value of the obstacle
 */
void GameField::addObstacle(int x, int y, int type)
{
  int health = 0;
  std::string tType = "Hedgehog";
  if (type == 'R'){
    tType = "Rock";
    health = 4;
  }else if (type == 'T'){
    tType = "Tree";
    health = 2;
  }else if (type == 'B'){
    tType = "Bush";
    health = 1;
  }else if (type == 'W'){
    tType = "Water";
  }else if (type == 'C'){
    tType = "Crate";
    health = 1;
  }else if (type == 'H'){
    tType = "Hedgehog";
  }
  fieldMap->tileMap[y][x] = Tile(tType, health, x, y, 4, nullptr);
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
  fieldMap->tileMap[y][x] = Tile("Empty", 0, x, y, 0, nullptr, nullptr);
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
std::vector<std::pair<int,int>> *GameField::getSFXPointer()
{
  std::vector<std::pair<int,int>> *temp;
  temp = &SFX;
  return temp;
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
      if(actors[i].name != "Projectile\n")
      {
        //std::cout << "Tank Down!! " << actors[i].name << " died\n";
        deceased.push_back(actors[i]);
        //std::cout << "Current number of dead tanks is: " << deceased.size() << endl;
        if (tracker != nullptr){
          tracker->killed(actors[i].id, actors[i].name);
        }
        fieldMap->tileMap[actors[i].y][actors[i].x].actor = nullptr;
      }else{
        fieldMap->tileMap[actors[i].y][actors[i].x].projectile = nullptr;
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
 * @return true if an obstacle exists at a tile (Or specific object), false if not
 *
 */
int GameField::obstacleAt(int x, int y)
{
  std::string tType = fieldMap->tileMap[y][x].type;
  int obj = 1;
  if(tType == "Rock")
    obj = 'R';
  else if (tType == "Water")
    obj = 'W';
  else if (tType == "Bush")
    obj = 'B';
  else if (tType == "Tree")
    obj = 'T';
  else if (tType == "Crate")
    obj = 'C';
  else if (tType == "Empty")
    obj = 0;
  return obj;
}

/**
 * @author Jon McKee
 * @par Description:
 * Returns the current game turn
 * 
 * @param[out] returns the current game turn
 */
int GameField::getGameTurn(){return gameTurn;}

/**
 * @author Jon McKee
 * @par Description:
 * Returns the current actor
 * 
 * @param[out] returns the current actor
 */
int GameField::getActTurn(){return actTurn;}

/**
 * @author Jon McKee
 * @par Description:
 * Returns the current modifier counter
 * 
 * @param[out] returns the current modifier counter
 */
int GameField::getModCounter(){return modCounter;}

/**
 * @author Jon McKee
 * @par Description:
 * Increments game turn counter
 */
void GameField::incTurn(){gameTurn++;}

/**
 * @author Jon McKee
 * @par Description:
 * Set the fieldMap to a loaded map file.
 */
void GameField::setMap(MapData * newMap){
    fieldMap = newMap;
  }