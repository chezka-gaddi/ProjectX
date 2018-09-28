/***********************************************************
 * @file
 *
 * @brief
 * This is the header file for the ActorInfo structure.
 * This structure will keep track of actors' stats so that 
 *	they are not modifiable by the players
 *
 ***********************************************************/

#ifndef __ACTOR_INFO_H
#define __ACTOR_INFO_H

#include "Actor.h"
#include "ProjectileActor.h"

/*! \struct ActorInfo
    \brief A structure containing Actor stats and info

    This structure will hold health, damage, x & y coordinates, id number, and range
*/
struct ActorInfo
{
    Actor *act_p;       /*!< */
    int health;       /*!<The health value of the Actor */
    int damage;       /*!<The damage value of the Actor */
    int x;      /*!<The x corrdinate location of the Actor */
    int y;      /*!<The y coordindate location of the Actor */
    int id;     /*!<The id number of the Actor */
    int range;    /*!<The Range value of the Actor */
    ActorInfo(Actor *a, int h, int d, int xpos, int ypos, int i) : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i) {}  /*!<The Constructor that will initialize the variables within the structure */
    ActorInfo(){}
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);

#endif
