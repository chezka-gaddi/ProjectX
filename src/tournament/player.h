/***************************************************************************//**
* @file player.h
* @author Jonathan McKee
* @brief Struct for the tournament players
*******************************************************************************/
#ifndef __player_h
#define __player_h

#include <string.h>

struct player{
    std::string name;
    int wins;
    int losses;
    int participated;
};

#endif