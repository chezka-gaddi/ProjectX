#include "ActorInfo.h"

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs)
{
    return (lhs.act_p == rhs.act_p && lhs.health == rhs.health && lhs.damage == rhs.damage && lhs.x == rhs.x &&
            lhs.y == rhs.y && lhs.id == rhs.id);
}
