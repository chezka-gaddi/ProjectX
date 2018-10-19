/*! \file */

#include "Actor.h"

/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * This constructor will set all member variables to zero/name
 *
 *****************************************************************************/
Actor::Actor()
{
    name = "";
    id = 0;
}

/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * This constructor will set all member variables to zero/name
 *
 *****************************************************************************/
Actor::Actor(std::string newName, int newId)
{
    name = newName;
    id = newId;
}

/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * Destructor as this is a base class and it is needed.
 *
 *****************************************************************************/
Actor::~Actor()
{

}
//Setters
/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * This member function will set the member variable name to a new value
 *         contained in newName.
 *
 * @param[in]        newName - The new string that name will be
 *
 *****************************************************************************/
void Actor::setName(std::string newName)
{
    name = newName;
}

/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * This member function will set the member variable id to a new value
 *         contained in newId.
 *
 * @param[in]        newId - The new id number that id will be
 *
*****************************************************************************/
void Actor::setId(int newId)
{
    name = newId;
}

//Getters
/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * This member function will return the value contained in the member variable
 *   id
 *
 * @return        id - The id number of the actor
 *
*****************************************************************************/
int Actor::getId()
{
    return id;
}

/**************************************************************************//**
 * @author John Weatherhead
 *
 * @par Description
 * This member function will return the value contained in the member variable
 *   name
 *
 * @return        name - The name string of the actor
 *
*****************************************************************************/
std::string Actor::getName()
{
    return name;
}
