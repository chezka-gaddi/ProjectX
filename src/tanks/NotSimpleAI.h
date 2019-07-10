#ifndef __SIMPLE_AI_H
#define __SIMPLE_AI_H

#include <actors/Actor.h>
#include <structures/direction.h>
#include <cmath>

class NotSimpleAI : public Actor
{
    int calcDist(int x1, int y1, int x2, int y2);

public:
#ifndef testing

    /**
     * calculates a move, and returns the data describing its move
     * @return MoveData the desired move to be made, if it is possible then the gamefield will do the move
     */
    virtual direction move(const MapData &map, PositionData status);

    /**
     * calculates an attack and returns the data describing its attack
     * @return Attack data the desired attack to be made, if possible the gamefield will do the move
     */
    virtual direction attack(const MapData &map, PositionData status);

    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);

    virtual int spendAP(const MapData &map, PositionData status);

    void updateMap(const MapData &map, PositionData status);
    bool lineOfFire(int x, int y, PositionData status);
    direction checkTargets(const MapData &map, PositionData status);
   
    attributes myStats; 
    NotSimpleAI();
    ~NotSimpleAI();

private:
    struct target{
        int x;
        int y;
        int health;
        int damaged;
    };

    bool spend = false;
    bool firstTurn = true;
    std::vector<std::vector<int>> heatMap;
    std::vector<target> targetList;
#endif
};

#endif
