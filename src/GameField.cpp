#include "GameField.h"

GameField::GameField()
{
    turnCount = 0;
    fieldWidth = 10;
    fieldHeight = 10;
    map.resize(100);
    std::fill(map.begin(), map.end(), 0);
}
GameField::GameField(int width, int height) : fieldWidth(width), fieldHeight(height)
{
    turnCount = 0;
    map.resize(width * height);
    std::fill(map.begin(), map.end(), 0);
}
int GameField::getTurnCount()
{
    return turnCount;
}
int GameField::getWidth()
{
    return fieldWidth;
}
int GameField::getHeight()
{
    return fieldHeight;
}
std::vector<int> GameField::getMap()
{
    return map;
}
void GameField::nextTurn()
{
    ++turnCount;
}
void GameField::addActor(Actor *a)
{
    actors.push_back(a);
}
std::vector<Actor *> GameField::getActors()
{
    return actors;
}
std::vector<Actor *> GameField::findActorsByCoord(int x, int y)
{
    std::vector<Actor *> hits;
    for (auto a : actors) //check each actor
    {
        if (a->getFieldX() == x && a->getFieldY() == y)
            hits.push_back(a);
    }
    return hits;
}
void GameField::cull()
{
    for (int i = 0; i < actors.size(); ++i)
    {
        if (actors[i]->getHealth() == 0)
            actors.erase(actors.begin()+i);
    }
}
