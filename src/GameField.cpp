#include "GameField.h"

/**
 * Default constructor, makes a 10x10 empty map
 */

GameField::GameField()
{
    turnCount = 0;
    fieldMap.width = 10;
    fieldMap.height = 10;
    fieldMap.map.resize(100);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
}
/**
 * Constructor given dimensions
 */
GameField::GameField(int width, int height)
{
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;
    fieldMap.map.resize(width * height);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
}
/**
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
}
/**
 * Gets the number of turns that have elapsed
 */
int GameField::getTurnCount()
{
    return turnCount;
}
/**
 * Gets the width of the field
 */
int GameField::getWidth()
{
    return fieldMap.width;
}
/**
 * Gets the height of the field
 */

int GameField::getHeight()
{
    return fieldMap.height;
}

/**
 * Gets just the map as a vector of ints
 */ 
std::vector<int> GameField::getMap()
{
    return fieldMap.map;
}
/**
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
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * AI's are culled
 */
void GameField::nextTurn()
{
    ++turnCount;
    direction dir;
    PositionData pos;
    AttackData atk;
    for (auto &a : actors)
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
        case up:
            if (a.y > 0)
                a.y--;
            break;
            
        case down:
            if (a.y < fieldMap.height-1)
                a.y++;
            break;
            
        case left:
            if (a.x > 0)
                a.x--;
            break;
                
        case right:
            if (a.x < fieldMap.width-1)
                a.x++ ;
            break;
        default:
            break;
        }

        //Get the AI's desired attack
        atk = a.act_p->attack(fieldMap, pos);
        for (auto &t :actors)
        {
            //Check if anyone was hit
            if (t.x == atk.attack_x && t.y == atk.attack_y && t.health > 0)
                t.health--;
        }
    }
    cull();
    updateMap();
}
/**
 * Add an actor to the list
 */
void GameField::addActor(ActorInfo a)
{
    actors.push_back(a);
    updateMap();
}

/**
 * Get the current set of actors
 */
std::vector<ActorInfo> GameField::getActors()
{
    return actors;
}
/**
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
 * Remove actors with hp of 0 from the game
 */
void GameField::cull()
{
    
    for (int i = 0; i < actors.size(); ++i) //This is used instead of the c++11 version so that we can use the index.
    {
        if (actors[i].health == 0)
            actors.erase(actors.begin()+i);
    }
    
}
