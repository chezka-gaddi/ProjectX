/**
 * @file GameField.cpp
 * @author David Donahue
 */
#include "GameField.h"

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
 * Executes the move and attack phase of each AI's turn and increments the turn counter.
 * AI's are culled
 */
void GameField::nextTurn()
{
    ++turnCount;
    direction dir;
    PositionData pos;
    AttackData atk;
    MoveData projMove;
    int projRange;
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
	projRange = 10;
        for(int i = 0; i < projRange; i++)
	{
            projMove = ProjectileActor.moveProjectile(fieldMap, pos);
	    a.x = a.x + projMove.new_x; 
	    a.y = a.y + projMove.new_y;
            atk = a.act_p->attack(fieldMap, pos);
            for (auto &t :actors)
            {
                //Check if anyone was hit
                if (t.x == atk.attack_x && t.y == atk.attack_y && t.health > 0)
                    t.health--;
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
            actors.erase(actors.begin()+i);
    }
    
}
