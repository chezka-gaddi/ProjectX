#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <GL/glut.h>

class Menu : public Drawable
{
public:
    Menu() {}
    ~Menu() {}
};

void drawBitmapText( char *string, float x, float y );
void drawStrokeText( char *string, float x, float y, float z );

#endif
