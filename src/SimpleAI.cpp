#include "SimpleAI.h"

SimpleAI::SimpleAI() {}
SimpleAI::~SimpleAI() {}

direction SimpleAI::move(MapData map, PositionData status)
{
    return stay;
}

AttackData SimpleAI::attack(MapData map, PositionData status)
{
    return AttackData(0,0,0);
}
