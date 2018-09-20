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
