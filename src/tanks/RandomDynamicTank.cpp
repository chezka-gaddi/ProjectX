//
// Created by jlee on 10/12/18.
//

#include "RandomDynamicTank.h"

direction RandomDynamicTank::move(MapData map, PositionData status) {
    srand(200);
    int choice = rand() % 4;

    if(choice == 0){
        return up;
    }
    else if( choice == 1){
        return down;
    }
    else if(choice == 2){
        return left;
    }
    else{
        return right;
    }
}

AttackData RandomDynamicTank::attack(MapData map, PositionData status) {
    return AttackData(0,0,0); //never attack
}

RandomDynamicTank::RandomDynamicTank() {}

std::string RandomDynamicTank::getName() {
    return "RandomDynamicTankActor";
}
