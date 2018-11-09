/**
 * @file GameField.cpp
 * @author David Donahue
 */
#include "GameField.h"
#include "game.h"
#include <iostream>

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
    for (auto &a : actors)
    {
        if (a.act_p != NULL)
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
    for (auto a : actors)
    {
        //for each actor fill in its id on the map
        if (a.health > 0)
            fieldMap.map[a.x+ fieldMap.width * a.y] = a.id;
    }

}
/***************************************************************************//**
 * @brief
 * Prompts the actors to choose attributes to specialize int
 * @author Riley Kopp
 ******************************************************************************/
void GameField::setSPECIAL(int points)
{   
    int sum =0;
    attributes baseStats;
    
    for(auto &actor: actors)
    {
        baseStats.tankHealth = actor.tankAttributes.tankHealth;
        baseStats.tankAP = actor.tankAttributes.tankAP;
        baseStats.tankRadar = actor.tankAttributes.tankRadar;
        baseStats.tankDamage = actor.tankAttributes.tankDamage;
        baseStats.tankAmmo = actor.tankAttributes.tankAmmo;
        
        actor.tankAttributes = actor.act_p->setAttribute(points, baseStats);

        sum = actor.tankAttributes.tankHealth 
                    + actor.tankAttributes.tankAP
                    + actor.tankAttributes.tankRadar 
                    + actor.tankAttributes.tankDamage
                    + actor.tankAttributes.tankAmmo;
        if (sum  <= points)
        {
            actor.health += actor.tankAttributes.tankHealth;
            actor.range += actor.tankAttributes.tankAP;
            actor.radar += actor.tankAttributes.tankRadar;
            actor.damage += actor.tankAttributes.tankDamage;
            actor.ammo += actor.tankAttributes.tankAmmo;
            if (actor.health > 8){
              actor.health = 8;
              printf("Health stat was too high, setting at 8.\n");
            }
            if (actor.range > 8){
              actor.range = 8;
              printf("AP stat was too high, setting at 8.\n");
            }
            if (actor.radar > 16){
              actor.radar = 16;
              printf("Radar stat was too high, setting at 16.\n");
            }
            if (actor.damage > 8){
              actor.damage = 8;
              printf("Damage stat was too high, setting at 8.\n");
            }
            if (actor.ammo > 8){
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
/**
 * @author David Donahue
 * @par Description:
 * Executes the move phase of an AI's turn
 * AI's are culled
 */
void GameField::runMoves(ActorInfo &a)
{

    int xoff = 0, yoff = 0, tHealth = 0, hit = 0;
    bool hitObj;
    PositionData pos;
    direction dir;


    //PositionData to give the AI
    pos.game_x = a.x;
    pos.game_y = a.y;
    pos.health = a.health;
    pos.id = a.id;
    pos.ammo = a.ammo;
    //get the AI's desired move
    MapData fog = fieldMap;
    create_fog_of_war(fog, a);
    dir = a.act_p->move(fog, pos);
    a.heading = (dir == STAY) ? a.heading : dir;
    //If it checks out, execute it
    //If the actor hits a wall or obstacle, do not execute the move and deal 1 damage
    if (a.health <= 0 || a.id == 0)//We arn't playing this game with dead actors anymore
        return;
    switch (dir)
    {
    case UP:
        if (a.y > 0 && (!obstacleAt(a.x, a.y - 1) 
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
        if (a.y < fieldMap.height-1 && (!obstacleAt(a.x, a.y + 1) 
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
        if (a.x > 0 && (!obstacleAt(a.x - 1, a.y) 
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
        if (a.x < fieldMap.width-1 && (!obstacleAt(a.x + 1, a.y)
                                   || obstacleAt(a.x + 1, a.y) == 'R' 
                                   || obstacleAt(a.x + 1, a.y) == 'T' 
                                   || obstacleAt(a.x + 1, a.y) == 'C' 
                                   || obstacleAt(a.x + 1, a.y) == 'B'
                                   || obstacleAt(a.x + 1, a.y) == 'W' ))
            xoff = 1;
        else
            a.health--;
        break;
    case UPLEFT:
        if (a.y > 0 && a.x > 0 && (!obstacleAt(a.x-1,a.y-1) 
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
        if (a.y > 0 && a.x < fieldMap.width-1 && (!obstacleAt(a.x+1, a.y-1) 
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
        if (a.y < fieldMap.height-1 && a.x > 0 && (!obstacleAt(a.x-1,a.y+1) 
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
        if (a.y < fieldMap.height-1 && a.x < fieldMap.width-1 && (!obstacleAt(a.x+1, a.y+1) 
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

    a.x += xoff;
    a.y += yoff;
    hitObj = checkObjectStrike(a);
    if (a.id > 0 && obstacleAt(a.x, a.y) == 'R')
    {
        a.x -= xoff;
        a.y -= yoff;
        hitObj == true;
        a.health--;
    }
    else if (a.id < 0 && obstacleAt(a.x, a.y) == 'C')
    {
        a.health--;
        crate_o_doom(a.x, a.y, a);
        removeObstacle(a.x, a.y);
        hitObj == true;
    }
    else if(a.id > 0 && obstacleAt(a.x, a.y) == 'W'){
      a.x -= xoff;
      a.y -= yoff;
      hitObj == true;
      a.health--;
    }

    if (a.health > 0 && hitObj == false)
    {
        for (int i = 0; i < actors.size(); ++i ) //check each actor
        {
            if (a.health > 0 && actors[i].health > 0  //Make sure neither is dead
                    && actors[i].x == a.x    //Make sure we're on the same column
                    && actors[i].y == a.y    //Make sure we're on the same row
                    && a.id != actors[i].id) //Make sure our tank doesn't damage itself
            {
                if (a.id > 0 && actors[i].id > 0) //Check tank to tank ramming
                {
                    //printf("Tank hit tank\n");
                    //Reverse the move
                    a.x -= xoff;
                    a.y -= yoff;
                    tHealth - actors[i].health;
                    actors[i].health -= a.health; //deal full health damage to target
                    hit += tHealth - 1;
                    a.hits++; //A tank hit is still a hit right?
                    if (actors[i].health <= 0)
                    {
                        SFX.push_back(make_pair(actors[i].x, actors[i].y));
                        actors[i].health = 0;
                        actors[i].damage = 0;
                        actors[i].id = 0;
                        actors[i].range = 0;
                        a.kills++;
                    }
                }
                else if(actors[i].id < 0)  //Check if we ran into a projectile (What we are doesn't matter)
                {
                    //printf("Projectile or Tank hit a projectile.\n");
                    hit += actors[i].health; //store future damage
                    actors[i].health -= a.health; //Destroy the projectile
                    if (a.id > 0 && -actors[i].id != a.id) //Give the owner a hit, but not a self hit and not a missile to missle hit
                        actorInfoById(-actors[i].id).hits++;
                }
                else if(a.id < 0)  //If we're a projectile and we hit a tank
                {
                    //printf("Projectile hit tank. %d hit %d\n",a.id,actors[i].id);
                    actors[i].health -= a.health; //damage the tank
                    hit += a.health;
                    if (a.id != -actors[i].id)      //no self hits
                        actorInfoById(-a.id).hits++;  //give our owner a hit
                    if (actors[i].health <= 0)
                    {
                        SFX.push_back(make_pair(actors[i].x, actors[i].y));
                        actors[i].health = 0;
                        actors[i].damage = 0;
                        actors[i].id = 0;
                        actors[i].range = 0;
                        actorInfoById(-a.id).kills++;  //give our owner a hit
                    }
                }
            }else if(actors[i].id < 0) //Check if we ran into a projectile (What we are doesn't matter)
            {
                //printf("Projectile or Tank hit a projectile.\n");
                hit += actors[i].damage; //store future damage
                actors[i].health -= a.health; //Destroy the projectile
                if (a.id > 0 && -actors[i].id != a.id) //Give the owner a hit, but not a self hit and not a missile to missle hit
                  actorInfoById(-actors[i].id).hits++; 
            }else if(a.id < 0) //If we're a projectile and we hit a tank
            {
              //printf("Projectile hit tank. %d hit %d\n",a.id,actors[i].id);
              actors[i].health -= a.damage; //damage the tank
              hit += a.damage;
              if (a.id != -actors[i].id)      //no self hits
                actorInfoById(-a.id).hits++;  //give our owner a hit
              if (actors[i].health <= 0)
              {
                SFX.push_back(make_pair(actors[i].x, actors[i].y));
                actors[i].health = 0;
                actors[i].damage = 0;
                actors[i].id = 0;
                actors[i].range = 0;
                actorInfoById(-a.id).kills++;  //give our owner a hit
              }
            }
        }
    }
    a.health -= hit;
    if (a.id < 0 && (a.health <= 0 || hitObj == true))
    {
        SFX.push_back(make_pair(a.x, a.y));
        a.damage = 0;
        a.id = 0;
        a.health = 0;
    }
    updateMap();

    if (displayCallback != NULL)
        displayCallback(fieldMap, actors, turnCount);

}

bool GameField::checkObjectStrike(ActorInfo &a)
{
  int tempOb = obstacleAt(a.x, a.y);
  int hits = 0;


  if (a.id > 0 || a.health < 0) //Get the non projectiles back out of here
          return false;


  if (tempOb == 0){  //if the spot is empty then we couldn't have hit anything
          //printf("Nothing hit at (%d, %d): %d Health: %d\n", a.x, a.y, tempOb, a.health);
          return false;
  }

  else if (tempOb == 'B' || tempOb == 'W'){
  			 //Bushes don't stop bullets 
          //We technically dont need this now since bushes dont do anything, but we can make them destroyable later?
          //printf("Bush hit.  Not stopping.\n");
          return false;
  }
  else if(tempOb == 'R')
  {
    //printf("Rock strike, log it.\n");
    for (auto& r : gameptr->rocks)
    {
          if (r->gridx == a.x && r->gridy == a.y && r->health > 0)
          {
            //printf("Found Rock strike, log it.\n");
            r->health -= a.damage;
            if (r->health <= 0)
            {
                //printf("Found Rock strike, log it.\n");
                r->health -= a.damage;
                if (r->health < 0)
                {
                    r->health = 0;
                    r->destroyed = turnCount;
            }
        }
    }
    else if (tempOb == 'T')
    {
          if (t->gridx == a.x && t->gridy == a.y && t->health > 0)
          {
            //printf("Found tree strike, chop it.\n");
            t->health -= a.damage;
            if (t->health <= 0)
            {
              t->health = 0;
              t->destroyed = 0;
            }
            return true;
          }
    }
    else if (tempOb == 'C')
    {
        //printf("Hit the crate.\n");
        for ( auto &c : gameptr->specials)
        {
            if (c->gridx == a.x && c->gridy == a.y && c->health > 0)
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
                for (auto &t : gameptr->trees)
                {
                    if (t->gridx == x_iter && t->gridy == y_iter && t->health > 0)
                    {
                        t->health--;
                    }
                }
                break;
            case 'C':
                for (auto &c : gameptr->specials)
                {
                    if (c->gridx == x_iter && c->gridy == y_iter && c->health > 0)
                    {
                        c->health--;
                        hit = crate_o_doom(c->gridx, c->gridy, a); //Chain reaction
                    }
                }
                break;
            case 'R':
                for (auto &r : gameptr->rocks)
                {
                    if (r->gridx == x_iter && r->gridy == y_iter && r->health > 0)
                    {
                        r->health--;
                    }
                }
                break;
            case 'B':
            default:
                for (auto &act : actors)
                {
                    if (act.x == x_iter && act.y == y_iter && act.health > 0)
                    {
                        //printf("Hit a tank at (%d, %d)\n",x_iter, y_iter);
                        act.health--;
                        if (act.health <= 0)
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
          if (map.obstacleMap[value] != 'T')
            new_map.map[value] = map.map[value];
          new_map.obstacleMap[value] = map.obstacleMap[value];
          if (map.obstacleMap[value] == 0 && map.map[value] != 0){
            for (auto act : actors){
              if ( act.x == x_iter && act.y == y_iter && act.health > 0) {
                      new_map.healthMap[value] = act.health;
              }
            }
          } 
          switch(obstacleAt(x_iter, y_iter)){ 
            case 'T':
              for (auto t : gameptr->trees)
              {
                if (t->gridx == x_iter && t->gridy == y_iter && t->health > 0)
                {
                  new_map.healthMap[value] = t->health;
                }
              }
              break;
            case 'C':
              for (auto c : gameptr->specials)
              {
                new_map.healthMap[value] = 1;
              }
              break;
            case 'R':
              for (auto r : gameptr->rocks)
              {
                if (r->gridx == x_iter && r->gridy == y_iter && r->health > 0)
                {
                  new_map.healthMap[value] = r->health;
                }
              }
              break;
            case 'B':
              for (auto b : gameptr->bushes)
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
    ++turnCount;

    direction atk;
    ActorInfo newProjectile;
    PositionData pos;
    int action;
    int act_ap;
    int tSize, tId;
    MapData fog_of_war = fieldMap;
    //printf("Turn number: %d\n",turnCount);
#ifndef TESTING
    for (Obstacles* t : gameptr->trees)
    {
      if (t->health <= 0)
      {
        t->regrow(turnCount);
      }
    }
              for (Obstacles* r : gameptr->rocks)
              {
                if (r->health <= 0)
                {
                  r->regrow(turnCount);
                }
              }
              for (Obstacles* b : gameptr->bushes)
              {
                if (b->health <= 0)
                {
                  b->regrow(turnCount);
                }
              }
#endif
    for (int i = 0; i < actors.size() && actors[i].health != 0; ++i)
    {
        act_ap = actors[i].range;
        while (act_ap > 0 && actors[i].id != 0)
        {
            fog_of_war = fieldMap;
            create_fog_of_war(fog_of_war, actors[i]);
            pos.game_x = actors[i].x;
            pos.game_y = actors[i].y;
            pos.health = actors[i].health;
            pos.id = actors[i].id;
            pos.ap = act_ap;
            pos.ammo = actors[i].ammo;
            action = actors[i].act_p->spendAP(fog_of_war, pos);
            if ( action == 1)
            {
                runMoves(actors[i]);
            }

            else if (action == 2)
            {
                //PositionData to give the AI
                pos.game_x = actors[i].x;
                pos.game_y = actors[i].y;
                pos.health = actors[i].health;
                pos.id = actors[i].id;

                //Get the AI's desired attack
                atk = actors[i].act_p->attack(fog_of_war, pos);


                if (actors[i].id > 0) //tanks attacking
                {
                    if (atk != STAY && actors[i].ammo >= 1)
                    {
                        actors[i].heading = atk;
                        ProjectileActor * proj = new ProjectileActor(atk);
                        newProjectile.range = 6;
                        newProjectile.id = -actors[i].id;
                        newProjectile.act_p = proj;
                        newProjectile.health = 1;
                        newProjectile.damage = actors[i].damage;
                        newProjectile.x = actors[i].x;
                        newProjectile.y = actors[i].y;
                        actors.insert(actors.begin() + i + 1, newProjectile);
                        actors[i].shots++;
                        actors[i].ammo--;
                    }
                    else if (atk != STAY)
                    {
                        //printf("Out of ammo... Out of ammo... Out of ammo... Reloading.  %d bullets left %d bullets fired.  ",actors[i].ammo,actors[i].shots);
                        actors[i].ammo = actors[i].max_ammo;
                        //printf("Back up to %d bullets.\n",actors[i].ammo);
                    }
                }

            }
            else if (action == 4)
            {
                actors[i].ammo = actors[i].max_ammo;
                //printf("Reloading... Reloading... Reloading\n");
            }
            --act_ap;

        }
    }

    cull();
    updateMap();
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
    for( auto &a : actors )
    {
        if( a.health + a.damage + a.range + a.shots > pointsAvailable)
        {
            a.health = 1;
            a.damage = 1;
            a.range = 1;
            a.shots = 1;
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
 * @author David Donahue
 * @par Description:
 * Get the current set of actors
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
 * Get the current set of SFX
 */
std::vector<std::pair<int,int>> GameField::getSFX()
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
    for (auto a : actors) //check each actor
    {
        if (a.x == x && a.y == y)
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
    for (int i = 0; i < actors.size(); ++i) //This is used instead of the c++11 version so that we can use the index.
    {
        if (actors[i].health == 0)
        {
            if(actors[i].name != "default\n")
            {
                //std::cout << "Tank Down!! " << actors[i].name << " died\n";
                deceased.push_back(actors[i]);
                //std::cout << "Current number of dead tanks is: " << deceased.size() << endl;
            }
            if (actors[i].act_p != NULL)
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
    for (auto &a : actors)
    {
        if (a.id == id)
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
    for (auto a : actors)
        if (a.health > 0 && a.id > 0)
            winner = a.name;
    return winner;
}
