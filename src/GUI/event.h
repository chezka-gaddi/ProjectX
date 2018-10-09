#ifndef _EVENT_H_
#define _EVENT_H_

#include <iostream>
#include <sstream>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "game.h"
#include "GameField.h"
#include "TankDrawable.h"

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
class KeyboardEvent : public Event
{
   /// The key involved in this event
   unsigned char key;
   /// The x-location of where the event took place
   int xLoc;
   /// The y-location of where the event took place
   int yLoc;

public:
   /// Constructor
   KeyboardEvent(unsigned char, int, int);

   void doAction(Game &);
};

class SpecialKeyboardEvent : public Event
{
   /// The key involved in this event
   int key;
   /// The x-location of where the event took place
   int xLoc;
   /// The y-location of where the event took place
   int yLoc;

public:
   /// Constructor
   SpecialKeyboardEvent(int, int, int);

   void doAction(Game &);
};
/***************************************************************************//**
 * @class
 ******************************************************************************/
class MouseClickEvent : public Event
{
   /// The button involved in the event
   int button;
   /// The state of the button for this event (e.g. up, down)
   int state;
   /// The x-location of where the event took place
   int xLoc;
   /// The y-location of where the event took place
   int yLoc;

public:
   /// Constructor
   MouseClickEvent(int, int, int, int);

   void doAction(Game &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class MouseDragEvent : public Event
{
   /// The x-location of where the event took place
   int xLoc;
   /// The y-location of where the event took place
   int yLoc;

public:
   /// Constructor
   MouseDragEvent(int, int);

   void doAction(Game &);
};

/***************************************************************************//**
 * @class
 ******************************************************************************/
class MouseMoveEvent : public Event
{
   /// The x-location of where the event took place
   int xLoc;
   /// The y-location of where the event took place
   int yLoc;

public:
   /// Constructor
   MouseMoveEvent(int, int);

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
