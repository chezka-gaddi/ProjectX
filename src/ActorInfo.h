/** ActorInfo.h
 * a struct to keep track of actors' stats so that they are not modifiable by the players
 */

#ifndef __ACTOR_INFO_H
#define __ACTOR_INFO_H

#include "Actor-Alternate.h"

struct ActorInfo
{
    Actor *act_p;
    int health;
    int damage;
    int x;
    int y;
    int id;
};

#endif
