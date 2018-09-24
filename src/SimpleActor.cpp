#include "SimpleActor.h"

direction SimpleActor::move(MapData map, PositionData status)
{
    return up;
}
AttackData SimpleActor::attack(MapData map, PositionData status)
{
    AttackData ret;
    ret.attack_x = 0;
    ret.attack_y = 0;
    return ret;
}
