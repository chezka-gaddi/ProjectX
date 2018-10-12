//
// Created by jlee on 10/12/18.
//

#ifndef SRC_LEFTDYNAMICTANK_H
#define SRC_LEFTDYNAMICTANK_H


#include <iostream>
#include "../Actor.h"

class LeftDynamicTank : public Actor {

public:
    LeftDynamicTank();


    direction move(MapData map, PositionData status) override;

    AttackData attack(MapData map, PositionData status) override;
};


extern "C" Actor * makeTank(){
    std::cout << "making left dynamic tank" << std::endl;
    return new LeftDynamicTank();
}

#endif //SRC_LEFTDYNAMICTANK_H
