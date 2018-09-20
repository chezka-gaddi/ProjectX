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


