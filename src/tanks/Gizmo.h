#ifndef __GIZMO_H
#define __GIZMO_H

#include <actors/Actor.h>
#include <structures/direction.h>

class Gizmo : public Actor
{
private:
    attributes myStats;

public:
    Gizmo();
    ~Gizmo();

    virtual direction move(const MapData &map, PositionData status);
    virtual direction attack(const MapData &map, PositionData status);
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
    virtual int spendAP(const MapData &map, PositionData status);
};

#endif