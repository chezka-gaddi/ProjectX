/***********************************************************
 * @file
 *
 * @brief
 * This is the header file for the ActorInfo structure.
 * This structure will keep track of actors' stats so that 
 *	they are not modifiable by the players
 *
 ***********************************************************/


#ifndef __ACTOR_INFO_H
#define __ACTOR_INFO_H

#include "Actor.h"
#include "ProjectileActor.h"
#include "attributes.h"
#include <iostream>
#include <memory>

/*! \struct ActorInfo
    \brief A structure containing Actor stats and info

    This structure will hold health, damage, x & y coordinates, id number, and range
*/

struct ActorInfo
{
    Actor *act_p;
    int health = 0;
    int damage = 0;
    int x;
    int y;
    int id = 0;
    int range = 0;
    int AP = 0;
    int hits = 0;
    int shots = 0;
    int radar = 0;
    int kills = 0;
    int ammo = 0;
    int max_health = 0;
    int max_ammo = 0;
    bool sMod = false;
    float scale = 1;
    std::string name = "default\n";
    attributes tankAttributes;
    direction heading;
    ActorInfo(Actor *a
              , int h  //Health
              , int d  //Damage
              , int xpos //x
              , int ypos //y
              , int i    //id
              , int ap = 1 //Action points
              , int r = 0 //Range
              , int s = 0 //Shots
              , int v = 0 //Radar
              , int b = 1 //ammo
              , std::string n = "default") 
                   : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), AP(ap), range(r), hits(0), shots(s), tankAttributes(), radar(v), max_health(h), ammo(b), max_ammo(b), name(n), kills(0), heading(RIGHT){}  
    ActorInfo() : act_p(NULL), health(0), damage(0), x(0), y(0), id(0), range(0), hits(0), shots(0), max_health(0), ammo(0), max_ammo(0), heading(RIGHT){}
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);

#endif
