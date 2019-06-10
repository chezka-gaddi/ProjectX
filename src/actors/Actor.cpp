/*! \file */

#include "../actors/Actor.h"
//Actor::Actor() {}
/**************************************************************************//**
 * @author Jon McKee
 * @par Description
 * This is the default deconstructor that is overrideent by inherited actors
 *****************************************************************************/
Actor::~Actor() {}


//Setters
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
