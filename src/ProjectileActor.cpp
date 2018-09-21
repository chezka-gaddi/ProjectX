//this file
#include <ProjectileActor.h>

using namespace std;

ProjectileActor::ProjectileActor()
{
	range = 10;
	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
}

MoveData ProjectileActor::move()
{
	int xDiff, yDiff; // variables used to for movement in each direction
	//struct for projectile's coordinates
	moveData moveProjectile;
	
	xDiff = endX - startX;
        yDiff = endY - startY;

        //scaling movement to be less than maximum range
        if(xDiff + yDiff > range)
       	{
            xDiff = float(xDiff / (xDiff + yDiff)) * range + 0.5;
            yDiff = float(yDiff / (xDiff + yDiff)) * range + 0.5;
        }

       	moveProjectile.new_x = startX + xDiff;
       	moveProjectile.new_y = startY +yDiff;
   	}
	
	return moveProjectile;
}

AttackData ProjectileActor::attack()
{
	AttackData attackProjectile;

	//Initialize variables
	attackProjectile.attack_x = fieldX;
	attackProjectile.attack_y = fieldY;
	attackProjectile.damage = 1;
	
	return attackProjectile;
}


//Getters
int ProjectileActor::getRange()
{
    return range;
}
int ProjectileActor::getStartX()
{
    return startX;
}
int ProjectileActor::getStartY()
{
    return startY;
}
int ProjectileActor::getEndX()
{
    return endX;
}
int ProjectileActor::getEndY()
{
    return endY;
}


//Setters
void ProjectileActor::setRange(int rangeUpdate)
{
    range = rangeUpdate;
}

void ProjectileActor::setStartX(int startXUpdate)
{
    startX = startXUpdate;
}

void ProjectileActor::setStartY(int startYUpdate)
{
    startY = startYUpdate;
}

void ProjectileActor::setEndX(int endXUpdate)
{
    endX = endXUpdate;
}

void ProjectileActor::setEndY(int endYUpdate)
{
    endY = endYUpdate;
}

