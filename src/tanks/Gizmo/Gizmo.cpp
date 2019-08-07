/*******************************************************************************
 * @file
 * @brief Gizmo Tank
 ******************************************************************************/
#include "include/Gizmo.h"
#include <iostream>

Gizmo::Gizmo() {}
Gizmo::~Gizmo() {}

/**
 * @author Chezka Gaddi
 * @par Description:
 * 
 * Calculates where to allocate special points and returns attributes for the
 * tank.
 * 
 * @param[in] pointsAvailable - number of points to be allocated
 * @param[in] baseStats - starting stats for all tanks
 * 
 * @return attributes for the tank 
 */
attributes Gizmo::setAttribute(int pointsAvailable, attributes baseStats)
{
    return baseStats;
}

/**
 * @author Chezka Gaddi
 * @par Description:
 * 
 * Determines which action to spend AP on.
 * 
 * @param[in] map - map of the area within range
 * @param[in] status - tank's position info within the map
 * 
 * @return action the tank is going to make
 */
int Gizmo::spendAP(const MapData &map, PositionData status)
{
    return 0;
}

/**
 * @author Chezka Gaddi
 * @par Description:
 * 
 * Determines the direction the tank is going to move to.
 * 
 * @param[in] map - map of the area within range
 * @param[in] status - tank's position info within the map
 * 
 * @return direction of the tank's movement
 */
direction Gizmo::move(const MapData &map, PositionData status)
{
    return UP;
}

/**
 * @author Chezka Gaddi
 * @par Description:
 * 
 * Determines the direction the tank is going to shoot a projectile.
 * 
 * @param[in] map - map of the area within range
 * @param[in] status - tank's position info within the map
 * 
 * @return direction of the tank's attack
 */
direction Gizmo::attack(const MapData &map, PositionData status)
{
    return UP;
}


#ifndef DYNAMIC
extern "C"
{
    Actor *maker()
    {
        return new Gizmo;
    }
}
#endif
