/**************************************************************************//**
* @file
*
* @brief The source code for the ActorInfo class
*
******************************************************************************/

#include "actors/ActorInfo.h"

/*******************************************************************//**
 * @author David Donahue
 *
 * @par Description:
 * This is the overload function for '==' operator.
 *
 **********************************************************************/

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs)
{
    return (lhs.act_p == rhs.act_p && lhs.health == rhs.health && lhs.x == rhs.x && lhs.y == rhs.y 
        && lhs.id == rhs.id);
}

/*******************************************************************//**
 * @author Jon McKee
 *
 * @par Description:
 * This is the overload function for '==' operator.
 *
 **********************************************************************/

bool operator !=(const ActorInfo& lhs, const ActorInfo& rhs)
{
    return !(lhs.act_p == rhs.act_p && lhs.health == rhs.health && lhs.x == rhs.x && lhs.y == rhs.y 
        && lhs.id == rhs.id);
}

