//this file
#include <ProjectileActor.h>

using namespace std;

ProjectileActor()
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
	
	//vertical movement
   	 if (startX == endX)
    	{
       	 moveProjectile.new_x = startX;
       	 moveProjectile.new_y = startY + range;
    	}
    	//horizontal movement
    	else if(startY == endY)
    	{
       	 moveProjectile.new_x = startX + range;
       	 moveProjectile.new_y = startY;
    	}
    	//diagonal cases
    	else
    	{
         xDiff = endX - startX;
         yDiff = endY - startY;

        //scaling movement to be less than maximum range
        if(xDiff + yDiff > range)
        {
            xDiff = float(xDiff / (xDiff + yDiff)) * range;
            yDiff = float(yDiff / (xDiff + yDiff)) * range;
        }

       	 moveProjectile.new_x = startX + xDiff;
       	 moveProjectile.new_y = startY +yDiff;
   	}
	
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

