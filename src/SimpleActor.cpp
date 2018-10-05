#include "SimpleActor.h"


/**
 * @author David Donahue
 * @par Description:
 * returns the direction selected at construction
 */
direction SimpleActor::move(MapData map, PositionData status)
{
    return dir;
}

/**
 * @author David Donahue
 * @par Description:
 * Attacks 0,0 with the damage set at construction
 */
AttackData SimpleActor::attack(MapData map, PositionData status)
{
    return atk;
}
SimpleActor::SimpleActor() : atk(0,0,0), dir (up) {}
SimpleActor::SimpleActor(direction mv, int d) : atk(0, 0, d), dir(mv) {}

void SimpleActor::setAttack(int x, int y, int d)
{
    atk.attack_x = x;
    atk.attack_y = y;
    atk.damage = d;
}

void SimpleActor::setMove(direction d)
{
    dir = d;
}
