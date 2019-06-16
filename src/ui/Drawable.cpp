#include "Drawable.h"

int Drawable::dirToDeg(direction d){
    switch (d){
        case UP:
            return 90;
        case UPRIGHT:
            return 45; 
        case RIGHT:
            return 0;
        case DOWNRIGHT:
            return -45;
        case DOWN:
            return -90;
        case DOWNLEFT:
            return -135;
        case LEFT:
            return 180;
        case UPLEFT:
            return 135;
        //Uknown direction for degrees defaulting to up
        case STAY:
        default:
            return 90;
    }
}
