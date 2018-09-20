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
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will return the value contained in the member variable
 *     name of the current object.
 * 
 * @returns name
 *
 ****************************************************************************/
string Actor::getName()
{
    return name;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will return the value contained in the member variable
 *     id of the current object.
 * 
 * @returns id
 *
 ****************************************************************************/
int Actor::getId()
{
    return id;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will return the value contained in the member variable
 *     field_x of the current object.
 * 
 * @returns field_x
 *
 ****************************************************************************/
int Actor::getFieldX()
{
    return field_x;
}

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

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will set the member variable field_x to a new value 
 *         contained in newFieldX.
 * 
 * @param[in]        newFieldX - The new int that field_x will be
 *
 ****************************************************************************/
void Actor::setFieldX(int newFieldX)
{
    field_x = newFieldX;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will set the member variable field_y to a new value 
 *         contained in newFieldY.
 * 
 * @param[in]        newFieldY - The new int that field_y will be
 *
 ****************************************************************************/
void Actor::setFieldY(int newFieldY)
{
    field_y = newFieldY;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will set the member variable health to a new value 
 *         contained in newHealth.
 * 
 * @param[in]        newHealth - The new int that health will be
 *
 ****************************************************************************/
void Actor::setHealth(int newHealth)
{
    health = newHealth;
}

/*************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description:
 * This member function will set the member variable damage to a new value 
 *         contained in newDamage.
 * 
 * @param[in]        newDamage - The new int damamge will be
 *
 ****************************************************************************/
void Actor::setDamage(int newDamage)
{
    damage = newDamage;
}

