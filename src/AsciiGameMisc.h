//
// Created by jlee on 9/24/18.
//

#ifndef SRC_ASCIIGAMEMISC_H
#define SRC_ASCIIGAMEMISC_H
#include "ActorInfo.h"
#include "GameField.h"
#include <vector>


#define tankId 2


bool isplayable(std::vector<ActorInfo> actorInfo);
void displayAscii(GameField gameField, std::vector<ActorInfo> actorInfo);

#endif //SRC_ASCIIGAMEMISC_H
