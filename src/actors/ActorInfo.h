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

#include <actors/Actor.h>
#include <actors/ProjectileActor.h>
#include <structures/attributes.h>
#include <iostream>
#include <memory>

/*! \struct ActorInfo
    \brief A structure containing Actor stats and info

    This structure will hold health, damage, x & y coordinates, id number, and range
*/
struct ActorInfo
{
    //Points to parts
    Actor *act_p = nullptr;  /*!< The pointer to the constructed actor */

    //Actor information
    std::string name = "default"; /*!< The actors stored name */
    int id = 0; /*!< The Actors ID number */
    int x = 0; /*!< The actors current X position */
    int y = 0; /*!< The actors current Y position */
    int prevx = -1; /*!< The previous X component for the actor (Used in animation) */
    int prevy = -1; /*!< The previous Y component for the actor (Used in animation) */
    direction heading; /*!< The actors heading*/
    
    //Actor Stats
    int health = 0;
    int max_health = 0; /*!< The max health for this actor*/
    int damage = 0;
    int AP = 0;
    int radar = 0;
    int range = 0;
    int ammo = 0;
    int max_ammo = 0; /*!< The max number of ammo for this actor */
    int shots = 0; /*!< The total number of shots made by the Actor */
    int hits = 0; /*!< The total number of hits made by the Actor */
    int kills = 0; /*!< The number of kills the actor has made */
    
    //Camping information
    int cDetect = 0; /*!< number of actions the actor has not moved */
    bool camp = false; /*!< Flag for checking if the actor is considered camping */
    bool sMod = false; /*!< Modular flag for smoke/fire trails */
    
    //Drawing information
    float scale = 1; /*!< */
    float offsetx = 0; /*!< The stored x offset for drawing the actor */
    float offsety = 0; /*!< The stored y offset for drawing the actor */
        
    //Default constructor for structure
    ActorInfo(Actor *a
              , std::string n = "default"
              , int i = 0   //id
              , int xpos = 0 //x
              , int ypos = 0 //y
              , int h = 0 //health
              , int mh = 0//max health
              , int d = 0//damage
              , int ap = 0//ap
              , int r = 0//radar
              , int rg = 0 //range
              , int am = 0//ammo
              , int ma = 0//max ammo
              ) 
                   : act_p(a), name(n), id(i), x(xpos), y(ypos), heading(UP), 
                   health(h), max_health(mh), damage(d), AP(ap),
                   radar(r), range(rg), ammo(am), max_ammo(ma), 
                   shots(0), hits(0), kills(0){} /*!< Constructor with options to set. */
    ActorInfo(){};
};

bool operator==(const ActorInfo& lhs, const ActorInfo& rhs); /*!< Overloaded comparison operator */

#endif
