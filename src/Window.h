//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_WINDOW_H
#define SLACKERS_PLATFORM_WINDOW_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <vector>
#include "Drawable.h"
#include "GameField.h"

class Window{

    int x_pos, y_pos;

    int width, hight;

    std::vector<Drawable*> drawables;//the things to draw
    GameField gameField;

public:
    /**
     * makes a window object
     */
    Window();
    /**
     * draws all of the drawables
     */
    void Draw();
    /**
     * clears the screen and draws all of the drawables
     */
    void ReDraw();

};


//just glut things

    //singleton:
Window* TANKGAMEWINDOW(){
        static Window*TANKGAMEWINDOW = new Window();

        return TANKGAMEWINDOW;
    }

    //callbacks (not set in stone)
//gets called when the window is resized
void resizeCallBack(int width, int height);
//gets called on a keypress
void keyboardCallBack(unsigned char key, int window_x, int window_y);
//gets called on a mouse click
void MouseCallBack(int button, int state, int window_x, int window_y);
//we may not use this one but it gets called if the mouse moves in the window
void passiveMouseCallBack(int window_x, int window_y);
//might want to do all of the glut initialization in its own function so main doesnt look bad
void glutInit(int screen_x, int screen_y, int width, int height);
#endif //SLACKERS_PLATFORM_WINDOW_H
