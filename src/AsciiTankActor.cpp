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
    cout << "Move (u d l r): ";
    cin >> c;

    switch (tolower(c))
    {
    case 'u':
        actorMove = up;
        break;
    case 'd':
        actorMove = down;
        break;
    case 'l':
        actorMove = left;
        break;
    case 'r':
        actorMove = right;
        break;
    default:
        actorMove = stay;
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

    cin.clear();
    cin.ignore(); //Ensure no characters are in the input buffer
    
    cout << "Enter the X and Y cooridinates you want to attack as X Y: ";
    cin >> x >> y;

    actorAttack.damage = 1;
    actorAttack.attack_x = x;
    actorAttack.attack_y = y;
    return actorAttack;
}



AsciiTankActor::AsciiTankActor() : enableConsole (false) {}
