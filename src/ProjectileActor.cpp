//this file
#include <ProjectileActor.h>

using namespace std;

ProjectileActor()
{
	range = 10;
	startX = field_x;
	startY = field_y;
	endX = startX;
	endY = startY;
}

MoveData ProjectileActor::move()
{
	static int moveSpeedX = 1;
	static int moveSpeedY = 1;
	//struct for projectile's coordinates
	moveData moveProjectile;
	
	//initialize data
	moveProjectile.new_x = startX;
	moveProjectile.new_y = staryY;
	
	//move projectile
	endX = startX + moveSpeedX;
	endY = startY + moveSpeedY;
	
	moveProjectile.new_x = endX;
	moveProjectile.new_y = endY;
	
	//update new start position of projectile
	startX = endX;
	startY = endY;
	
	return moveProjectile;
}

AttackData attack()
{
	AttackData attackProjectile;

	//Initialize variables
	attackProjectile.attack_x = startX;
	attackProjectile.attack_y = startY;
	attackProjectile.damage = 1;
	
	return attackProjectile;
}

