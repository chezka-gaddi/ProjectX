#include "GameField.h"

GameField::GameField()
{
    turnCount = 0;
    fieldMap.width = 10;
    fieldMap.height = 10;
    fieldMap.map.resize(100);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
}
GameField::GameField(int width, int height)
{
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;
    fieldMap.map.resize(width * height);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
}
GameField::GameField(int width, int height, std::vector<ActorInfo> acts) : actors(acts)
{
    turnCount = 0;
    fieldMap.width = width;
    fieldMap.height = height;
    fieldMap.map.resize(width * height);
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    updateMap();
}
int GameField::getTurnCount()
{
    return turnCount;
}
int GameField::getWidth()
{
    return fieldMap.width;
}
int GameField::getHeight()
{
    return fieldMap.height;
}
std::vector<int> GameField::getMap()
{
    return fieldMap.map;
}
void GameField::updateMap()
{    
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    for (auto a : actors)
    {
        fieldMap.map[a.x+ fieldMap.width * a.y] = a.id;
    }
    
}
void GameField::nextTurn()
{
    ++turnCount;
    direction dir;
    PositionData pos;
    for (auto &a : actors)
    {
        pos.game_x = a.x;
        pos.game_y = a.y;
        pos.health = a.health;
        pos.id = a.id;
        dir = a.act_p->move(fieldMap, pos);
        switch (dir)
        {
        case up:
            a.y--;
            break;
            
        case down:
            a.y++;
            break;
            
        case left:
            a.x--;
            break;
                
        case right:
            a.x++;
            break;
        default:
            break;
            }
    }
    updateMap();
}
void GameField::addActor(ActorInfo a)
{
    actors.push_back(a);
    updateMap();
}
std::vector<ActorInfo> GameField::getActors()
{
    return actors;
}
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
void GameField::cull()
{
    
    for (int i = 0; i < actors.size(); ++i)
    {
        if (actors[i].health == 0)
            actors.erase(actors.begin()+i);
    }
    
}
