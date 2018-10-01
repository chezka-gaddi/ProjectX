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
    direction heading;
ActorInfo(Actor *a, int h, int d, int xpos, int ypos, int i, int r) : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), range(r), heading(up) {}
    ActorInfo(Actor *a, int h, int d, int xpos, int ypos, int i) : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), range(1), heading(up) {}
    ActorInfo(){}
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);

#endif
