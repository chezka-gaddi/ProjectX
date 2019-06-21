#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

/*********************//*
 * @author Original Development Team
 * @author Jon McKee
 * @brief these are the default stats for a tank object.
 * All values default to 0 but can be set by users or the
 * game map via constructor
 *
 ***********************/
struct attributes
{
    int tankHealth = 0;
    int tankDamage = 0;
    int tankAP = 0;
    int tankRadar = 0;
    int tankAmmo = 0;
    int projRange = 0;
    int tankSpecial = 0;
    attributes( int tH = 0, int tD = 0, int tR = 0, int tV = 0, int tA = 0, int pR = 0, int tS = 0) 
       : tankHealth(tH), tankDamage(tD), tankAP(tR), tankRadar(tV), tankAmmo(tA), projRange(pR), tankSpecial(tS) {}

};

#endif
