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

GameField::GameField()
{
    turnCount = 0;
    fieldMap.width = 10;
    fieldMap.height = 10;
    fieldMap.map.resize(100);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
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
GameField::GameField(int width, int height)
{
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;
    fieldMap.map.resize(width * height);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    displayCallback = NULL;
}
/**
 * @author David Donahue
 * @par Description:
 * Constructor with dimensions and a vector of ActorInfo
 */
GameField::GameField(int width, int height, std::vector<ActorInfo> acts) : actors(acts)
{
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;
    fieldMap.map.resize(width * height);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    updateMap();
    displayCallback = NULL;
}

GameField::GameField(int width, int height, std::vector<ActorInfo> startActors, void (*d_callback)(MapData, std::vector<ActorInfo>)) : actors(startActors)
{
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;
    fieldMap.map.resize(width * height);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
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
        fieldMap.map[a.x+ fieldMap.width * a.y] = a.id;
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
    int rangeCount;
    PositionData pos;
    direction dir;
    
    rangeCount = a.range;
    while (rangeCount)
    {
        //PositionData to give the AI
        pos.game_x = a.x;
        pos.game_y = a.y;
        pos.health = a.health;
        pos.id = a.id;
        //get the AI's desired move
        dir = a.act_p->move(fieldMap, pos);
            
        //If it checks out, execute it
        switch (dir)
        {
        case direction::up:
            if (a.y > 0)
                a.y--;
            else
                a.health--;
            a.heading=direction::up;
            break;
                
        case direction::down:
            if (a.y < fieldMap.height-1)
                a.y++;
            else
                a.health--;
            a.heading=direction::down;
            break;
                
        case direction::left:
            if (a.x > 0)
                a.x--;
            else
                a.health--;
            a.heading=direction::left;
            break;
                
        case direction::right:
            if (a.x < fieldMap.width-1)
                a.x++;
            else
                a.health--;
            a.heading=direction::right;
            break;
        default:
            break;
        }

    
        
        collisionVect.erase(collisionVect.begin(), collisionVect.end()); //blank the vector
        for (int i = 0; i < actors.size(); ++i ) //check each actor
        {
            if (actors[i].x == a.x && actors[i].y == a.y)
                collisionVect.push_back(i);
        }
            
        if (collisionVect.size() > 1)
        {
            collisionDamage = 0;
            for (auto i: collisionVect)
            {
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
            rangeCount = 0;
            a.damage = 0;
            a.id = 0;
        }
        else
            --rangeCount;

            updateMap();

        if (displayCallback != NULL)
            displayCallback(fieldMap, actors);
        
    }
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

    AttackData atk;
    ActorInfo newProjectile;
    PositionData pos;
    for (int i = 0; i < actors.size(); ++i)
    {
        runMoves(actors[i]);

        if(actors[i].health != 0)
        {
            //PositionData to give the AI
            pos.game_x = actors[i].x;
            pos.game_y = actors[i].y;
            pos.health = actors[i].health;
            pos.id = actors[i].id;
                
            //Get the AI's desired attack
            atk = actors[i].act_p->attack(fieldMap, pos);


            if (atk.damage > 0)
            {
                if (actors[i].id > 0) //tanks attacking
                {
                    ProjectileActor * proj = new ProjectileActor;
                    proj->setEndX(atk.attack_x);
                    proj->setEndY(atk.attack_y);
                    proj->setStartX(actors[i].x);
                    proj->setStartY(actors[i].y);
                    newProjectile.range = 6;
                    newProjectile.id = -actors[i].id;
                    newProjectile.act_p = proj;
                    newProjectile.health = 1;
                    newProjectile.damage = 1;
                    newProjectile.x = actors[i].x;
                    newProjectile.y = actors[i].y;
                    actors.insert(actors.begin() + i + 1, newProjectile);
                }
                else //projectiles requesting a self destruct
                {
                    actors[i].health = 0;
                    actors[i].id = 0;
                    actors[i].range = 0;
                    actors[i].damage = 0;

                    //update the display
                    updateMap();
                    if (displayCallback != NULL)
                        displayCallback(fieldMap, actors);
                }
                
            }
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
