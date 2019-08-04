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
    int id;
    int wins;
    int losses;
    int participated;
    std::string images;

    bool operator<(const player &p){
        return (this->id < p.id);
    }
};

#endif