#ifndef __SIMPLE_AI_H
#define __SIMPLE_AI_H

#include <actors/Actor.h>
#include <structures/direction.h>
#include <cmath>
#include <ostream>
#include <iostream>

class NotSimpleAI : public Actor
{
    int calcDist(int x1, int y1, int x2, int y2);

public:
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
    void checkTargets(const MapData &map, PositionData status);
    void updateTargets(const MapData &map, PositionData status);
    int calcDist(direction dir, int dx, int dy, PositionData status);
   
    attributes myStats; 
    NotSimpleAI();
    ~NotSimpleAI();
    
    struct target{
        int dist;
        int x;
        int y;
        int health;
        int damage;
        int id;
        bool bullet = false;

        target( int d, int nx, int ny, int h, int dam, int i = 0, bool b = false) : dist(d), x(nx), y(ny), health(h), damage(dam), id(i), bullet(b){}

        bool operator<(const target& a) const
        {
            //false = 0, true = 1
            return (a.bullet < bullet || (a.bullet == bullet && dist < a.dist));
        }

        friend std::ostream& operator<<(std::ostream& os, const NotSimpleAI::target& t);

    };

private:
    bool spend = false;
    bool firstTurn = true;
    std::vector<std::vector<int>> heatMap;
    std::vector<target> targetList;
};

#endif
