/**
 * @file GameField.cpp
 * @author David Donahue
 */
#include "GameField.h"
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
    std::fill(fieldMap.obstacleMap.begin(), fieldMap.obstacleMap.end(), false);
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
    for(auto &actor: actors)
    {
        actor.tankAttributes = actor.act_p->setAttribute(points);
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

    std::vector<int> collisionVect;
    int collisionDamage;
    PositionData pos;
    direction dir;


    //PositionData to give the AI
    pos.game_x = a.x;
    pos.game_y = a.y;
    pos.health = a.health;
    pos.id = a.id;
    //get the AI's desired move
    dir = a.act_p->move(fieldMap, pos);
    a.heading = (dir == STAY) ? a.heading : dir;
    //If it checks out, execute it
    //If the actor hits a wall or obstacle, do not execute the move and deal 1 damage
    switch (dir)
    {
    case UP:
        if (a.y > 0 && !obstacleAt(a.x, a.y - 1))
            a.y--;
        else
            a.health--;
        break;

    case DOWN:
        if (a.y < fieldMap.height-1 && !obstacleAt(a.x, a.y + 1))
            a.y++;
        else
            a.health--;
        break;

    case LEFT:
        if (a.x > 0 && !obstacleAt(a.x - 1, a.y))
            a.x--;
        else
            a.health--;
        break;

    case RIGHT:
        if (a.x < fieldMap.width-1 && !obstacleAt(a.x + 1, a.y))
            a.x++;
        else
            a.health--;
        break;
    case UPLEFT:
        if (a.y > 0 && a.x > 0 && !obstacleAt(a.x-1,a.y-1))
        {
            a.y--;
            a.x--;
        }
        else
            a.health--;
        break;

    case UPRIGHT:
        if (a.y > 0 && a.x < fieldMap.width-1 && !obstacleAt(a.x+1, a.y-1))
        {
            a.y--;
            a.x++;
        }
        else
            a.health--;
        break;

    case DOWNLEFT:
        if (a.y < fieldMap.height-1 && a.x > 0 && !obstacleAt(a.x-1,a.y+1))
        {
            a.y++;
            a.x--;
        }
        else
            a.health--;
        break;

    case DOWNRIGHT:
        if (a.y < fieldMap.height-1 && a.x < fieldMap.width-1 && !obstacleAt(a.x+1, a.y+1))
        {
            a.y++;
            a.x++;
        }
        else
            a.health--;
        break;

    default:
        break;
    }

    bool tankInCollision = false;

    collisionVect.erase(collisionVect.begin(), collisionVect.end()); //blank the vector
    for (int i = 0; i < actors.size(); ++i ) //check each actor
    {
        if (actors[i].x == a.x && actors[i].y == a.y)
        {
            collisionVect.push_back(i);
            if (actors[i].id > 0)
                tankInCollision = true;
        }

    }

    if (collisionVect.size() > 1 && a.health > 0)
    {
        collisionDamage = 0;
        for (auto i: collisionVect)
        {
            if(!(actorInfoById(-actors[i].id) == nullActor) && tankInCollision)
            {
                actorInfoById(-actors[i].id).hits++;
            }
            collisionDamage += actors[i].damage;
        }
        for (auto i: collisionVect) //apply the portion from the other actors
        {
            actors[i].health -= (collisionDamage - actors[i].damage);
            if (actors[i].health < 0)
                actors[i].health = 0;
            if (actors[i].health == 0)
            {
                actors[i].damage = 0;
                actors[i].id = 0;
                actors[i].range = 0;
            }
        }
    }
    if (a.health == 0)
    {
        a.damage = 0;
        a.id = 0;
    }
    
    updateMap();

    if (displayCallback != NULL)
        displayCallback(fieldMap, actors, turnCount);

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
    int act_ap;
    for (int i = 0; i < actors.size(); ++i)
    {
        act_ap = actors[i].range;
        while (act_ap > 0)
        {
            pos.game_x = actors[i].x;
            pos.game_y = actors[i].y;
            pos.health = actors[i].health;
            pos.id = actors[i].id;
            pos.ap = act_ap;

            if (actors[i].act_p->spendAP(fieldMap, pos) == 1)
                runMoves(actors[i]);
            
            else if (actors[i].act_p->spendAP(fieldMap, pos) == 2)
            {
                if(actors[i].health != 0)
                {
                    //PositionData to give the AI
                    pos.game_x = actors[i].x;
                    pos.game_y = actors[i].y;
                    pos.health = actors[i].health;
                    pos.id = actors[i].id;

                    //Get the AI's desired attack
                    atk = actors[i].act_p->attack(fieldMap, pos);


                    if (actors[i].id > 0) //tanks attacking
                    {
                        if (atk != STAY)
                        {
                            actors[i].heading = atk;
                            ProjectileActor * proj = new ProjectileActor(atk);
                            newProjectile.range = 6;
                            newProjectile.id = -actors[i].id;
                            newProjectile.act_p = proj;
                            newProjectile.health = 1;
                            newProjectile.damage = 1;
                            newProjectile.x = actors[i].x;
                            newProjectile.y = actors[i].y;
                            actors.insert(actors.begin() + i + 1, newProjectile);
                            actors[i].shots++;
                        }
                    }
            
                }
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

void GameField::addObstacle(int x, int y)
{
    fieldMap.obstacleMap[x + fieldMap.width * y] = true;
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
bool GameField::obstacleAt(int x, int y)
{
    return fieldMap.obstacleMap[x + y * fieldMap.width];
}
