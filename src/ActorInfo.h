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

/*! \struct ActorInfo
    \brief A structure containing Actor stats and info

    This structure will hold health, damage, x & y coordinates, id number, and range
*/

struct ActorInfo
{
    Actor *act_p;
    int health;
    int damage;
    int x;
    int y;
    int id;
    int range;
    int hits;
    int shots;
    int radar;
    int kills;
    int ammo;
    int max_health;
    int max_ammo;
    std::string name = "default\n";
    attributes tankAttributes;
    direction heading;
    ActorInfo(Actor *a
              , int h  //Health
              , int d  //Damage
              , int xpos //x
              , int ypos //y
              , int i    //id
              , int r = 0 //Range
              , int s = 0 //Shots
              , int v = 0 //Radar
              , int b = 1 //ammo
              , std::string n = "default") 
                   : act_p(a), health(h), damage(d), x(xpos), y(ypos), id(i), range(r), hits(0), shots(s), tankAttributes(), radar(v), max_health(h), ammo(b), max_ammo(b), name(n), kills(0), heading(RIGHT){}  
    ActorInfo() : act_p(NULL), health(0), damage(0), x(0), y(0), id(0), range(0), hits(0), shots(0), max_health(0), ammo(0), max_ammo(0), heading(RIGHT){}
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs);

#endif
