#include <iostream>
#include "AsciiTankActor.h"

using std::cout;
using std::cin;
using std::endl;


direction AsciiTankActor::move( MapData map, PositionData status)
{
   char decision = 0;
   direction movement = stay;

   cout << "Enter in a direction to move" << endl;
   cout << "w (up) d (down) a (left) d (right) p (stay):" << endl;
   
   cin >> decision;

   switch (decision)
   {
	case 'w' :
		movement = up;
		break;
	case 's' :
		movement = down;
		break;
	case 'a' :
		movement = left;
		break;
	case 'd' :
		movement = right;
		break;
	case 'p' :
		movement = stay;
		break;
	default:
		cout << "Not a valid direction" << endl;
		cout << "Your turn will be skipped" << endl;
		movement = stay;
   }
   return movement;
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
