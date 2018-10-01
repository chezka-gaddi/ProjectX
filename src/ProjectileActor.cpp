//this file
#include <ProjectileActor.h>

using namespace std;
/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This constructor will initialize start/end variables to 0 and range to 10.
 *
******************************************************************************/
ProjectileActor::ProjectileActor()
{
	range = 10;
	startX = 0;
	startY = 0;
	endX = 0;
	endY = 0;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This constructor will set the member values of ProjectileActor to passed in
 * values.
 *
******************************************************************************/
ProjectileActor::ProjectileActor(int newRange, int newStartX, int newStartY,
				int newEndX, int newEndY)
{
	range = newRange;
        startX = newStartX;
        startY = newStartY;
        endX = newEndX;
        endY = newEndY;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will find the difference on each coordinate direction between
 * the start position and desired end position of a projectile. If the
 * difference is larger than the projectile's range, it is scaled down to fit
 * within that maximum range per movement. Then the MoveData struct is set
 * to the calculated values to actually move the projectile.
 *
 * @returns MoveProjectile - struct with new coordinates to move to
******************************************************************************/
MoveData ProjectileActor::move(MapData map, PositionData status)
{
	//temporary variables used for movement calculation in each direction
	float xDiff, yDiff;
	float degree, tangent;
	float xDirection, yDirection;

	//struct for projectile's coordinates
	MoveData moveProjectile;
	
	//calculates how far to move each position
	xDiff = abs(endX - status.game_x);
        yDiff = abs(status.game_y - endY);
	
	//to avoid division by 0, this is checked first
	if(xDiff == 0)
	{
		moveProjectile.new_x = 0;
		moveProjectile.new_y = 1;
	}
	else
	{
		//calculates the angle of projectile tan(x) = yDiff / xDiff
		tangent = yDiff / xDiff;
        	degree = atan(tangent) * 180 / 3.14159;
		//set incrementation of projectile based on angle
		if(degree < 30) //moves horizontal
		{
			moveProjectile.new_x = 1;
			moveProjectile.new_y = 0;
		}
		else if(degree > 60) //moves vertically
		{
			moveProjectile.new_x = 0;
			moveProjectile.new_y = 1;
		}
		else //moves diagonally
		{
			moveProjectile.new_x = 1;
			moveProjectile.new_y = 1;
		}
	}
	//account of direction of projectile
	xDirection = endX - status.game_x;
	yDirection = status.game_y - endY;

	if(xDirection == 0 && yDirection != 0)
	{
		 yDirection = yDirection / abs(yDirection);
	}
	else if(yDirection == 0 && xDirection != 0)
	{
		xDirection = xDirection / abs(xDirection);
	}
	else if(xDirection == 0 && yDirection == 0)
	{
		moveProjectile.new_x = 0;
		moveProjectile.new_y = 0;
		return moveProjectile;
	}
	else
	{
		xDirection = xDirection / abs(xDirection);
		yDirection = yDirection / abs(yDirection);
	}

	//multiplies by 1 or -1 depending on direction of movement
	moveProjectile.new_x = moveProjectile.new_x * xDirection;
	moveProjectile.new_y = moveProjectile.new_y * yDirection; 

	return moveProjectile;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Descript`ion
 * This function will declare an AttackData struct and initialize the values to
 * the current positon on the field and damage to 1. It then returns that
 * struct.
 * 
 * @returns attackProjectile - struct with data on where to attack and damage
******************************************************************************/
AttackData ProjectileActor::attack(MapData map, PositionData status)
{
	AttackData attackProjectile;

	//Initialize variables
	attackProjectile.attack_x = status.game_x;
	attackProjectile.attack_y = status.game_y;
	attackProjectile.damage = 1;
	
	return attackProjectile;
}


//Getters
/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will get the value of member variable range in ProjectileActor
 *
 * @returns range - the range of the projectile
 *
******************************************************************************/
int ProjectileActor::getRange()
{
    return range;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will get the value of member variable startX in ProjectileActor
 *
 * @returns startX - the starting x-coordinate of the projectile
 *
******************************************************************************/
int ProjectileActor::getStartX()
{
    return startX;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will get the value of member variable startY in ProjectileActor
 *
 * @returns startY - the starting y-coordinate of the projectile
 *
******************************************************************************/
int ProjectileActor::getStartY()
{
    return startY;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will get the value of member variable endX in ProjectileActor
 *
 * @returns endX - the ending x-coordinate of the projectile
 *
******************************************************************************/
int ProjectileActor::getEndX()
{
    return endX;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will get the value of member variable endY in ProjectileActor
 *
 * @returns endY - the ending y-coordinate of the projectile
 *
******************************************************************************/
int ProjectileActor::getEndY()
{
    return endY;
}

/******************************************************************************
 * @author Riley Kopp
 * 
 * @par Description
 * This function will get the value of member variable newX in ProjectileActor
 *
 * @returns newX - the ending x-coordinate of the projectile
 *
******************************************************************************/
int ProjectileActor::getNewX()
{
    return newX;
}

/******************************************************************************
 * @author Riley Kopp
 * 
 * @par Description
 * This function will get the value of member variable newY in ProjectileActor
 *
 * @returns newY - the ending y-coordinate of the projectile
 *
******************************************************************************/
int ProjectileActor::getNewY()
{
    return newY;
}
//Setters

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will set the value of member variable range in ProjectileActor
 * to the new value passed in.
 *
 * @param[in] rangeUpdate - the new range of the projectile
 *
******************************************************************************/
void ProjectileActor::setRange(int rangeUpdate)
{
    range = rangeUpdate;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will set the value of member variable startX in ProjectileActor
 * to the new value passed in.
 *
 * @param[in] startXUpdate - the new starting x-coordinate of the projectile
 *
******************************************************************************/
void ProjectileActor::setStartX(int startXUpdate)
{
    startX = startXUpdate;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will set the value of member variable startY in ProjectileActor
 * to the new value passed in.
 *
 * @param[in] startYUpdate - the new starting y-coordinate of the projectile
 *
******************************************************************************/
void ProjectileActor::setStartY(int startYUpdate)
{
    startY = startYUpdate;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will set the value of member variable endX in ProjectileActor
 * to the new value passed in.
 *
 * @param[in] endXUpdate - the new ending x-coordinate of the projectile
 *
******************************************************************************/
void ProjectileActor::setEndX(int endXUpdate)
{
    endX = endXUpdate;
}

/******************************************************************************
 * @author Brad Peterson
 * 
 * @par Description
 * This function will set the value of member variable endY in ProjectileActor
 * to the new value passed in.
 *
 * @param[in] endYUpdate - the new ending y-coordinate of the projectile
 *
******************************************************************************/
void ProjectileActor::setEndY(int endYUpdate)
{
    endY = endYUpdate;
}

