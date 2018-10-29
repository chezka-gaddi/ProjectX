/*! \file */
#include "ProjectileActor.h"

using namespace std;
/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * This constructor will initialize start/end variables to 0 and range to 10.
 *
******************************************************************************/
ProjectileActor::ProjectileActor()
{
}

/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * This constructor will set the member values of ProjectileActor to passed in
 * values.
 *
******************************************************************************/
ProjectileActor::ProjectileActor(direction d) : dir(d) {}

/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description:
 * 
******************************************************************************/
direction ProjectileActor::move(MapData map, PositionData status)
{
    return dir;

}

/**************************************************************************//**
 * @author Brad Peterson
 *
 * @par Description
 * This function will declare an AttackData struct and initialize the values to
 * the current positon on the field and damage to 1. It then returns that
 * struct.
 *
 * @param[in] map - the data for our current gamefield dimensions
 * @param[in[ status - the data containing actor position
 *
 * @returns attackProjectile - struct with data on where to attack and damage
******************************************************************************/
direction ProjectileActor::attack(MapData map, PositionData status)
{
    return STAY;
}


/**************************************************************************//**
 * @author Brad Peterson
 * 
 * @par Description
 * Returns attributes of projectile
 *
 * @returns projAttributes - attributes of projectile
 *
******************************************************************************/
attributes ProjectileActor::setAttribute(int pointsAvailable)
{
    attributes projAttributes;

    return projAttributes;
}

/**
 * @author David Donahue
 * @par Description
 * Returns descision to (0) end turn, (1) move, or (2) attack
 */
int ProjectileActor::spendAP(MapData map, PositionData status)
{
    return 1;
}
