//
// Created by 7401123 on 9/12/18.
//

#ifndef SRC_TURNDATA_H
#define SRC_TURNDATA_H


#include "Actor.h"
#include "AttackData.h"
#include "MoveData.h"
/**
 * this is mostly used for the inner workings of the gamefield
 */
struct TurnData {
    Actor *actor;
    AttackData attackData;
    MoveData moveData;
};


#endif //SRC_TURNDATA_H
