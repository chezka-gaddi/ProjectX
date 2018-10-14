/**************************************************************************//**
* @file
*
* @brief The source code for the AsciiTankActor class
*
******************************************************************************/

#include <iostream>
#include "AsciiTankActor.h"

using std::cout;
using std::cin;
using std::endl;


/*************************************************************************//**
 * @author Youki Lewis
 *
 * @par Description:
 * This member function will return the actorMove variable 
 * 
 * @param[in]        map - the map the tanks are on
 * @param[in]        status - the current state of the ActorInfo's
 *
 ****************************************************************************/

direction AsciiTankActor::move( MapData map, PositionData status)
{
    char c;
    cout << "Player " << status.id<< ": Move (u d l r): ";
    cin >> c;

    switch (tolower(c))
    {
    case 'u':
        actorMove = UP;
        break;
    case 'd':
        actorMove = DOWN;
        break;
    case 'l':
        actorMove = LEFT;
        break;
    case 'r':
        actorMove = RIGHT;
        break;
    default:
        actorMove = STAY;
        break;
    }
    return actorMove;
}



/*************************************************************************//**
 * @author Youki Lewis
 *
 * @par Description:
 * This member function will return the actorAttack variable 
 * 
 * @param[in]        map - the map the tanks are on
 * @param[in]        status - the current state of the ActorInfo's
 *
 ****************************************************************************/
AttackData AsciiTankActor::attack( MapData map, PositionData status)
{
    int x, y;
    char c;
    cin.clear();
    cin.ignore(); //Ensure no characters are in the input buffer

    cout << "Attack (y,n)? ";
    cin >> c;

    if (tolower(c) != 'y')
        return AttackData(0,0,0);

    cin.clear();
    cin.ignore(); //Ensure no characters are in the input buffer
    
    cout << "Player " << status.id << ": Enter the X and Y cooridinates you want to attack as X Y: ";
    cin >> x >> y;

    actorAttack.damage = 1;
    actorAttack.attack_x = x;
    actorAttack.attack_y = y;
    return actorAttack;
}



AsciiTankActor::AsciiTankActor() {}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new AsciiTankActor;
    }
}
#endif
