/***************************************************************************//**
* @file bracket.h
* @author Jonathan McKee
* @brief Struct for the tournament brackets
*******************************************************************************/
#ifndef __bracket_h
#define __bracket_h

#include <string.h>

struct bracket{
    std::string mapName;
    std::string stats;
    std::string images;
    std::string settings;
    std::string spawns;
    int players = 2;
    int rounds = 1;
};

#endif