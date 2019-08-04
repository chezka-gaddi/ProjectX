/***************************************************************************//**
* @file gameover.h
* @author Jonathan McKee
* @brief Contains the code for end game functions
*******************************************************************************/
#ifndef __gameover_h
#define __gameover_h

#include <vector>
#include <string>


#include <settings/Settings.h>
#include <actors/ActorInfo.h>


int gameOver(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner, std::shared_ptr<Settings> settings, int turn);
void displayScoreBoard(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner, std::shared_ptr<Settings> settings, int winDex);
#endif