//
// Created by jlee on 9/24/18.
//

#ifndef SRC_ASCIIGAMEMISC_H
#define SRC_ASCIIGAMEMISC_H
#include "ActorInfo.h"
#include "GameField.h"
#include <vector>

//depending on what we make the tankactor's ids this is mostly used for displaying right now
/***
 * tankId = 2 by default should be changed in the future
 */
#define tankId 2

//determines if the current gamefield is playable
/***
 * determines if the current game field is playable
 * @param actorInfo a vector of actor info
 * @return bool true if 2 or more tanks are in the vector
 */
bool isplayable(std::vector<ActorInfo> actorInfo);
//displays the ascii representation of the game
/***
 * displays the ascii representation of the game
 * @param gameField a gamefield
 * @param actorInfo actorInfo a vector of actorinfo structs
 */
void displayAscii(MapData map, std::vector<ActorInfo> actors, int turnCount);

enum gameMode {ai, sp, mp};

void gameloop(gameMode mode);


#endif //SRC_ASCIIGAMEMISC_H
