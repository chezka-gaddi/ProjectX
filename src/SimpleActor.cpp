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
    AttackData ret;
    ret.attack_x = 0;
    ret.attack_y = 0;
    ret.damage = damage;
    return ret;
}
SimpleActor::SimpleActor() : damage (0), dir (up) {}
SimpleActor::SimpleActor(direction mv, int d) : damage(d), dir(mv) {}
