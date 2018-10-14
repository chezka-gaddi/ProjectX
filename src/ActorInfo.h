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
    Actor *act_p;
    int health;
    int damage;
    int x;
    int y;
    int id;
    int range;
    int hits;
    int shots;

    ActorInfo(Actor *a, int h, int d, int xpos, int ypos, int i, int r) : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), range(r), hits(0), shots(0) {}

    ActorInfo(Actor *a, int h, int d, int xpos, int ypos, int i) : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), range(1), hits(0), shots(0) {}

    ActorInfo() {}
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);

#endif
