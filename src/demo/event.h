#ifndef _EVENT_H_
#define _EVENT_H_

#include <iostream>
#include <sstream>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "game.h"
#include "Drawable.h"

using namespace std;

#define ESCAPE_KEY 27

/***************************************************************************//**
 * @class Event
 ******************************************************************************/
class Event
{
    public:
        virtual void doAction(Game&) = 0;
        virtual ~Event();
};

class InitEvent : public Event
{
    int columns, rows;
    public:
        InitEvent(int, int);

        void doAction(Game &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class DisplayEvent : public Event
{
    public:
        void doAction(Game &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class ReshapeEvent : public Event
{
   int width;
   int height;

    public:
        ReshapeEvent(int, int);

        void doAction(Game &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class TimerEvent : public Event
{
    unsigned int tick;
    
    public:
        TimerEvent(int);

        void doAction(Game &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class CloseEvent : public Event
{
    public:
        CloseEvent();

        void doAction(Game &);
};
#endif
