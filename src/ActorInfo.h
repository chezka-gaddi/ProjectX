/** ActorInfo.h
 * a struct to keep track of actors' stats so that they are not modifiable by the players
 */

#ifndef __ACTOR_INFO_H
#define __ACTOR_INFO_H

#include "Actor.h"
#include "ProjectileActor.h"

struct ActorInfo
{
    Actor *act_p;
    int health;
    int damage;
    int x;
    int y;
    int id;
    int range;
    ActorInfo(Actor *a, int h, int d, int xpos, int ypos, int i) : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i) {}
    ActorInfo(){}
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);

#endif
