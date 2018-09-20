#include "GameField.h"

GameField::GameField()
{
    turnCount = 0;
    
}
int GameField::getTurnCount()
{
    return turnCount;
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
