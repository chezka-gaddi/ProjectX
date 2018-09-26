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
