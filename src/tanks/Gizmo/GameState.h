/**
 * @file
 * @brief Contains the 
 */

#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include <structures/attributes.h>
#include <structures/MoveData.h>
#include <structures/PositionData.h>

struct GameState
{
    attributes myAttributes;
    PositionData status;
};

#endif