#include "SimpleActor.h"
#include "attributes.h"


/**
 * @author David Donahue
 * @par Description:
 * returns the direction selected at construction
 *
 * @param[in] map - MapData with the current game map
 * @param[in] status - information about the current actor including position and ID
 */
direction SimpleActor::move(MapData map, PositionData status)
{
    return dir;
}

/**
 * @author David Donahue
 * @par Description:
 * Attacks 0,0 with the damage set at construction
 *
 * @param[in] map - MapData with the current game map
 * @param[in] status - information about the current actor including position and ID
 */
AttackData SimpleActor::attack(MapData map, PositionData status)
{
    return atk;
}
/**
 * @author David Donahue
 * @par Description:
 * Default constructor, sets default move to up and attack to 0,0
 */
SimpleActor::SimpleActor() : atk(0,0,0), dir (UP) {}

/**
 * @author David Donahue
 * @par Description:
 * Constructor with desired direction and damage to attack 0,0 with
 * 
 * @param[in] mv : the desired default move
 * @param[in] d : the desired attack damage
 */
SimpleActor::SimpleActor(direction mv, int d) : atk(0, 0, d), dir(mv) {}

/**
 * @author David Donahue
 * @par Description:
 * Set the desired point and damage to return on attack()
 *
 * @param[in] x - x coordinate to attack
 * @param[in] y - y coordinate to attack
 * @param[in] d - damage of the projectile
 */
void SimpleActor::setAttack(int x, int y, int d)
{
    atk.attack_x = x;
    atk.attack_y = y;
    atk.damage = d;
}

/**
 * @author David Donahue
 * @par Description:
 * Set the desired direction to move on the next turn
 *
 * @param[in] d - direction to move 
 */
void SimpleActor::setMove(direction d)
{
    dir = d;
}

/**
 * @author Youki Lewis
 * @par Description:
 * Sets the attributes for the tanks decided by the AI
 *
 * @parm[in] pointsAvailable - available points for distribution
 */
attributes SimpleActor::setAttribute(int pointsAvailable)
{
    attributes tankAttributes;
    int basicDistribution = pointsAvailable / 4;
    int leftoverPoints = pointsAvailable % 4;
    int randChoice = 0;
    
    tankAttributes.tankHealth = basicDistribution;
    tankAttributes.tankDamage = basicDistribution;
    tankAttributes.tankRange = basicDistribution;
    tankAttributes.tankShots = basicDistribution;
        
    while (leftoverPoints != 0)
    {
      randChoice = rand() % 4;
          
      switch( randChoice )
      {
          case 0:
              tankAttributes.tankHealth += 1;
              break;
          case 1:
              tankAttributes.tankDamage += 1;
              break;
          case 2:
              tankAttributes.tankRange += 1;
              break;
          case 3:
              tankAttributes.tankShots += 1;
              break;
          default:
              tankAttributes.tankHealth += 1;
          }
        }

    return tankAttributes;
}


#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new SimpleActor;
    }
}
#endif
