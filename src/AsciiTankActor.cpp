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
 * This member function will set the variable actorMove as the value contained
 *	within decision
 * 
 * @param[in]        decision - 
 *
 ****************************************************************************/

void AsciiTankActor::setMove( direction decision )
{
   actorMove = decision;

   return;
   
}

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
    if (enableConsole) 
    {
        cout << "Move: ";
        cin >> c;

        switch (c)
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
    }
    return actorMove;
}

/*************************************************************************//**
 * @author Youki Lewis
 *
 * @par Description:
 * This member function will set the member variable id to a new value 
 *         contained in newId.
 * 
 * @param[in]        xAttack - The value attack_x will be set as 
 * @param[in]        yAttack - The value attack_y will be set as
 * @param[in]        numDamage - The value damage will be set as 
 *
 ****************************************************************************/
void AsciiTankActor::setAttackData( int xAttack, int yAttack, int numDamage)
{
   actorAttack.attack_x = xAttack;
   actorAttack.attack_y = yAttack;
   actorAttack.damage = numDamage;
  
   return;
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
    if (enableConsole)
    {
        cout << "Enter the X and Y cooridinates you want to attack as X Y: ";
        cin >> x >> y;
        actorAttack.damage = 1;
        actorAttack.attack_x = x;
        actorAttack.attack_y = y;
    }
    return actorAttack;
}



AsciiTankActor::AsciiTankActor() : enableConsole (false) {}
AsciiTankActor::AsciiTankActor(bool cen) : enableConsole(cen) {}
