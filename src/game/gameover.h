/***************************************************************************//**
* @file gameover.h
* @author Jonathan McKee
* @brief Contains the code for end game functions
*******************************************************************************/
#ifndef __gameover_h
#define __gameover_h

#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <iostream>
#include <GL/freeglut.h>
#include <unistd.h>

#include <settings/Settings.h>
#include <actors/ActorInfo.h>
#include <ui/global.h>


void gameOver(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner, Settings * settings);
void displayScoreBoard(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner, Settings * settings, int winDex);
#endif