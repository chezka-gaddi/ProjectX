#ifndef __ATTRIBUTES_
#define __ATTRIBUTES_

struct attributes
{
    int tankHealth;
    int tankDamage;
    int tankRange;
    int tankShots;
    int tankRadar;

    attributes( int tH, int tD, int tR, int tS, int tV ) : tankHealth(tH), 
    tankDamage(tD), tankRange(tR), tankShots(tS), tankRadar(tV) {}
    
    attributes(){}

};

#endif
