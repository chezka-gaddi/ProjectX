/******************************************************
 * This file contains the function definitions for all
 *    functions within the Actor Class
 ******************************************************/
#include "Actor.h"

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This constructor will set all member variables to zero/name
 *
 ****************************************************************************/
Actor::Actor()
{
   name = "";
   id = 0;
   field_x = 0;
   field_y = 0;
   health = 0;
   damage = 0;   
}
/*************************************************************************//**
 * @author David Donahue
 *
 * @par Description:
 * Destructor as this is a base class and it is needed.
 *
 ****************************************************************************/
Actor::~Actor()
{}
/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will return the value contained in the member variable
 *     field_y of the current object.
 * 
 * @returns field_y
 *
 ****************************************************************************/
int Actor::getFieldY()
{
    return field_y;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will return the value contained in the member variable
 *     health of the current object.
 * 
 * @returns health
 *
 ****************************************************************************/
int Actor::getHealth()
{
    return health;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will return the value contained in the member variable
 *     damage of the current object.
 * 
 * @returns damage
 *
 ****************************************************************************/
int Actor::getDamage()
{
    return damage;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will set the member variable name to a new value 
 *         contained in newName.
 * 
 * @param[in]        newName - The new string that name will be
 *
 ****************************************************************************/
void Actor::setName(string newName)
{
    name = newName;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will set the member variable id to a new value 
 *         contained in newId.
 * 
 * @param[in]        newId - The new int that id will be
 *
 ****************************************************************************/
void Actor::setId(int newId)
{
    id = newId;
}


