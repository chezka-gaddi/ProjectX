
/*******************************************************//**
 * @file
 *
 * @brief
 * This is the header file for the AsciiTankActor class
 *
 ************************************************************/

#ifndef	ASCIITANKACTOR_H
#define ASCIITANKACTOR_H

#include "Actor.h"
/***************************************************************************//**
* @class AsciiTankActor
* @author Youki Lewis
* @par Description
* The basic tank actor for testing
******************************************************************************/
class AsciiTankActor : public Actor
{

    direction actorMove; 
    AttackData actorAttack;
    bool enableConsole;
public:
    virtual direction move(MapData map, PositionData status);    /*!<Returns the actorMove member variable */
    virtual AttackData attack(MapData map, PositionData status); /*!<Returns the actorAttack member variable */

    AsciiTankActor();

};

#endif
