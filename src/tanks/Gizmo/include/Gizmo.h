/**
 * @file
 * @brief Gizmo tank header file.
 */

#pragma once
#ifndef __GIZMO_H
#define __GIZMO_H

#include "actors/Actor.h"
#include "GameState.h"
#include "PlayStyle.h"

#include <vector>
#include <iostream>
using namespace std;

class Gizmo : public Actor
{
private:
    attributes myStats;
    //vector<vector<Tile>> map;

    //GameState *State;
    //PlayStyle *Strategy;

public:
    enum PlayStyles
    {
        Defensive,
        Aggressive,
        Sniper
    };

    Gizmo();
    ~Gizmo();

    virtual direction move(const MapData &map, PositionData status);
    virtual direction attack(const MapData &map, PositionData status);
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
    virtual int spendAP(const MapData &map, PositionData status);
};

#endif
