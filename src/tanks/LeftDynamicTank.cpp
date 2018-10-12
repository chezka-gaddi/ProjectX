//
// Created by jlee on 10/12/18.
//

#include "LeftDynamicTank.h"

LeftDynamicTank::LeftDynamicTank() {
    name = "LeftDynamicTank";
}

direction LeftDynamicTank::move(MapData map, PositionData status) {
    return left;
}

AttackData LeftDynamicTank::attack(MapData map, PositionData status) {
    return AttackData(0,0,0);
}
