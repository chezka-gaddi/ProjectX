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
    /*
    std::fill(fieldMap.map.begin(), fieldMap.map.end(), 0);
    for (auto a : actors)
    {
        fieldMap.map[a->getFieldX() + fieldMap.width * a->getFieldY()] = a->getId();
    }
    */
}
void GameField::nextTurn()
{
    ++turnCount;
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
    /*
    std::vector<Actor *> hits;
    for (auto a : actors) //check each actor
    {
        if (a->getFieldX() == x && a->getFieldY() == y)
            hits.push_back(a);
    }
    return hits;
    */
}
void GameField::cull()
{
    /*
    for (int i = 0; i < actors.size(); ++i)
    {
        if (actors[i]->getHealth() == 0)
            actors.erase(actors.begin()+i);
    }
    */
}
