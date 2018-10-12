//
// Created by jlee on 10/12/18.
//

#ifndef SRC_RANDOMDYNAMICTANK_H
#define SRC_RANDOMDYNAMICTANK_H


#include "../Actor.h"
//simple tank for testing dynamic loading
class RandomDynamicTank : public Actor {
    direction dir;
    AttackData atk;

public:
    //overload of the Actor::Actor() constructor
    RandomDynamicTank();
    /***
     * chooses a random direction and moves there
     * @param map map data
     * @param status tank status
     * @return enum:Direction a direction {left right up down}
     */
    direction move(MapData map, PositionData status) override;
    /**
     * doesnt attack
     * @param map map data
     * @param status tank status
     * @return AttackData (0,0,0)
     */
    AttackData attack(MapData map, PositionData status) override;
    /**
     * used by the dynamic loader
     * @return
     */
    std::string getName() override;
};

/**
 * This is a function used by the dynamic loader to construct a RandomDynamicTank , and it returns it as an actor
 * the extern "C" is there to avoid c++ function name mangling. because of how the class structure is set up the program
 * doesnt need to know that this tank is a random dynamic tank just that it is of type actor if this function is not in
 * any similar header files that will be turned into a shared library then the library will not be dynamically loadable
 */
extern "C" Actor * makeTank(){
    return new RandomDynamicTank();
}

#endif //SRC_RANDOMDYNAMICTANK_H
