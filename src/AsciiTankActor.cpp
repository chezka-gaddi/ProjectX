#include "AsciiTankActor.h"

using namespace std;

MoveData AsciiTankActor::move()
{
   MoveData playerMove;
   
   cout << "Where would you like to go?" << endl;
   cout << "Enter your x then y:" << endl;
   cin >> playerMove.new_x >> playerMove.new_y;

   return playerMove;
}

AttackData AsciiTankActor::attack()
{
   AttackData playerAttack;

   playerAttack.damage = 1;

   cout << "Where would you like to attack?" << endl;
   cout << "Enter your x then y:" << endl;
   cin >> playerAttack.attack_x >> playerAttack.attack_y;
   
   return playerAttack;
}
