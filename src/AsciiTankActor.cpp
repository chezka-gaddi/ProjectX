#include <iostream>
#include "AsciiTankActor.h"

using std::cout;
using std::cin;
using std::endl;


direction AsciiTankActor::move( MapData map, PositionData status)
{
   char decision = 0;

   cout << "Enter in a direction to move" << endl;
   cout << "u (up) d (down) a (left) d (right) :" << endl;
   
   decision = getchar();
   
   switch (decision)
   {
	case 'u' :
		return up;
	case 's' :
		return down;
	case 'a' :
		return left;
	case 'd' :
		return right;
	default:
		cout << "Not a valid direction" << endl;
		decision = 0;
   }
}

AttackData AsciiTankActor::attack( MapData ma, PositionData status)
{
   AttackData playerAttack;

   playerAttack.damage = 1;

   cout << "Enter an x coordinate for your attack:" << endl;
   cin >> playerAttack.attack_x;
   cout << "Enter an y coordinate for your attack:" << endl;
   cin >> playerAttack.attack_y;
   
   return playerAttack;
}
