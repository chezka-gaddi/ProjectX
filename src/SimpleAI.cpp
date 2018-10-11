#include "SimpleAI.h"
SimpleAI::SimpleAI() {}
SimpleAI::~SimpleAI() {}

direction SimpleAI::move(MapData map, PositionData status)
{
    return stay;
}

AttackData SimpleAI::attack(MapData map, PositionData status)
{
    AttackData ret(0,0,0);
    for (auto i : map.map)
    {
        if (i && i != status.id)
            ret.damage = 1;
    }
    return ret;
}
