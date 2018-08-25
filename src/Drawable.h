//
// Created by jlee on 8/25/18.
//

#ifndef SLACKERS_PLATFORM_DRAWABLE_H
#define SLACKERS_PLATFORM_DRAWABLE_H
class Drawable{

protected:

    //all drawables need to have a screen position
    int screen_x, screen_y;

    //this is for the future, if we dont need it, then we can delete it later it will be used for easy hiding of objects
    bool to_draw;

public:

    virtual void draw() = 0;
};
#endif //SLACKERS_PLATFORM_DRAWABLE_H
