/***************************************************************************//**
* @file Event.h
* @author Chezka Gaddi
* @brief Contains all functions prototypes that maintains the Event class and all
* of it's subclasses
*******************************************************************************/
#ifndef _EVENT_H_
#define _EVENT_H_

#include <iostream>
#include <sstream>
#include <GL/glut.h>

#include "game.h"
#include "Drawable.h"

using namespace std;

#define ESCAPE_KEY 27

/***************************************************************************//**
* @author Paul Hinker
* @class Event
* @brief Event is the parent class for all event classes and has a doAction
* and destructor function that must be overwritten by subclasses.
*******************************************************************************/
class Event
{
public:
    virtual void doAction(Game&) = 0;
    virtual ~Event();
};


/***************************************************************************//**
* @author Paul Hinker
* @class initEvent
* @brief Creates an event depending on what trigger was set off.
*******************************************************************************/
class InitEvent : public Event
{
    int columns, rows;

public:
    InitEvent(int, int);

    void doAction(Game &);
};


/***************************************************************************//**
* @author Paul Hinker
* @class DisplayEvent
* @brief Created when a display event is triggered
*******************************************************************************/
class DisplayEvent : public Event
{
public:
    void doAction(Game &);
};


/***************************************************************************//**
* @author Paul Hinker
* @class ReshapeEvent
* @brief Created when a reshape event is triggered
*******************************************************************************/
class ReshapeEvent : public Event
{
    int width;
    int height;

public:
    ReshapeEvent(int, int);

    void doAction(Game &);
};


/***************************************************************************//**
* @author Paul Hinker
* @class TimerEvent
* @brief Created when a timer event is triggered
*******************************************************************************/
class TimerEvent : public Event
{
    unsigned int tick;

public:
    TimerEvent(int);

    void doAction(Game &);
};


/***************************************************************************//**
* @author Paul Hinker
* @class CloseEvent
* @brief Created when a close event is triggered
*******************************************************************************/
class CloseEvent : public Event
{
public:
    CloseEvent();

    void doAction(Game &);
};
#endif
