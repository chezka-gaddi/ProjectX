//
// Created by jlee on 8/25/18.
//

/** @file */

#ifndef SLACKERS_PLATFORM_DRAWABLE_H
#define SLACKERS_PLATFORM_DRAWABLE_H

#include <string>

class Drawable{

protected:

    std::string name;  /*!<The name of teh drawable */
    int id;            /*!<The id number of the drawable */
    int screen_x;      /*!<The screen x coordinate of the drawable */
    int screen_y;      /*!<The scren y coordinate of the drawable */
    int health;        /*!<The health value of the drawable */

    //this is for the future, if we dont need it, then we can delete it later it will be used for easy hiding of objects
    bool to_draw; /*!<The variable deciding whether or not to draw the drawable */

public:

    virtual void draw() = 0; /*!<A pure virtual function to ensure drawable objects define how they are drew */ 
};
#endif //SLACKERS_PLATFORM_DRAWABLE_H
