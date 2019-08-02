/**
 * @file
 * @brief Includes Strategy Pattern for PlayStyle
 */

#ifndef __PLAYSTYLE_H
#define __PLAYSTYLE_H

#include "GameState.h"

class PlayStyle
{
public:
    PlayStyle(GameState *state) {}
    ~PlayStyle() {}

private:
    virtual int spendAP() = 0;
};

class Defensive : public PlayStyle
{
public:
    Defensive(GameState *state) : PlayStyle(state) {}

private:
    int spendAP();
};

class Aggressive : public PlayStyle
{
public:
    Aggressive(GameState *state) : PlayStyle(state) {}

private:
    int spendAP();
};

class Sniper : public PlayStyle
{
public:
    Sniper(GameState *state) : PlayStyle(state) {}

private:
    int spendAP();
};
#endif