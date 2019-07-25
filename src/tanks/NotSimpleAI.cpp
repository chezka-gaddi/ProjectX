#include "NotSimpleAI.h"
#include <iostream>
#include <algorithm>

NotSimpleAI::NotSimpleAI() {}
NotSimpleAI::~NotSimpleAI() {}

/**
 * @author David Donahue
 * @par Description:
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return direction to move
 */
direction NotSimpleAI::move(const MapData &map, PositionData status)
{
    int min_dist = map.width * map.height + 1;
    direction ret = STAY;
    int mHeight = map.height/2, mWidth = map.width/2;
    int x_pos = status.game_x, y_pos = status.game_y;
    int offset = 2; //lee way for moving
    unsigned int i = 0;
    int tempDist;
    
    if (spend == true){
      //Debug for testing mapupdate
      /*printf("Move Map:\n");
      for (int i = 0; i < map.map.size(); i++){
      printf("%d ", map.map[i]);
      if (i % 30 == 29)
            printf("\n");
      }
      printf("X: %d, Y: %d\n", status.game_x, status.game_y);*/
    }
    //Check target list first
    //printf("Checking Targetlist before Moving: \n");
    while( i < targetList.size() ){
        if (targetList[i].health > targetList[i].damage && !targetList[i].bullet){ //Only move towards tanks
            //find direction of tank
            for (int j = 0; j < 8; j++){
                tempDist = calcDist((direction) j, targetList[i].x, targetList[i].y, status);
                if ( tempDist <= min_dist){
                    //printf("New direction found: %d with distance: %d.\n", j, tempDist );
                    min_dist = tempDist;
                    ret = (direction) j;
                }else{
                    //printf("Old direction kept: %d, with distance: %d, checked distance %d.\n", (int) ret, min_dist, tempDist);
                }
            }
        }else{
            //printf("Bad target found: %d/%d health/damage.\n", targetList[i].health, targetList[i].damage);
        }
        i++;
    }

    if (ret != STAY)
        return ret;

    for (int x = 1; x <= map.width; ++x)
    {
        for (int y = 1; y <= map.height; ++y)
        {
            if ( map.tileMap[y][x].tank != nullptr &&
                    map.tileMap[y][x].tank->id != status.id &&
                    map.tileMap[y][x].tank->id != -status.id &&
                    calcDist(status.game_x, status.game_y, x, y) < min_dist &&
                    calcDist(status.game_x, status.game_y, x, y) > 1)
            {
                min_dist = calcDist(status.game_x, status.game_y, x, y);

                if (std::abs(status.game_x - x) > std::abs(status.game_y - y)) //more horizontal distance
                {
                    if (status.game_x > x)
                    {
                        //Safe to move
                        if (map.tileMap[y_pos][x_pos - 1].type == "Empty" || map.tileMap[y_pos][x_pos - 1].type == "Tree" || map.tileMap[y_pos][x_pos - 1].type == "Bush")
                        {
                            ret = LEFT;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_y > y) ? UP : DOWN; //avoid it up or down
                        }
                    }
                    else
                    {
                        //Safe to move
                        if (map.tileMap[y_pos][x_pos + 1].type == "Empty" || map.tileMap[y_pos][x_pos + 1].type == "Tree" || map.tileMap[y_pos][x_pos + 1].type == "Bush")
                        {
                            ret = RIGHT;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_y > y) ? UP : DOWN; //avoid it up or down
                        }
                    }

                }
                else
                {
                    if (status.game_y > y)
                    {
                        //Safe to move
                        if (map.tileMap[y_pos - 1][x_pos].type == "Empty" || map.tileMap[y_pos - 1][x_pos].type == "Tree" || map.tileMap[y_pos - 1][x_pos].type == "Bush")
                        {
                            ret = UP;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_x > x) ? LEFT : RIGHT; //avoid it left or right
                        }
                    }
                    else
                    {
                        //Safe to move
                        if (map.tileMap[y_pos + 1][x_pos].type == "Empty" || map.tileMap[y_pos + 1][x_pos].type == "Tree" || map.tileMap[y_pos + 1][x_pos].type == "Bush")
                        {
                            ret = DOWN;
                        }
                        else //obstacle in the way
                        {
                            ret = (status.game_x > x) ? LEFT : RIGHT; //avoid it left or right
                        }
                    }
                }
            }
        }
    }
    //Move towards center if we can't find anyone
    if (x_pos < mWidth - offset && y_pos < mHeight - offset && ret == STAY)
    {
        ret = DOWNRIGHT;
    }
    if (x_pos < mWidth - offset && y_pos > mHeight + offset && ret == STAY)
    {
        ret = UPRIGHT;
    }
    if (x_pos > mWidth + offset && y_pos < mHeight - offset && ret == STAY)
    {
        ret = DOWNLEFT;
    }
    if (x_pos > mWidth + offset && y_pos > mHeight + offset && ret == STAY)
    {
        ret = UPLEFT;
    }
    if (x_pos < mWidth - offset && ret == STAY)
    {
        ret = RIGHT;
    }
    if (y_pos > mHeight + offset && ret == STAY)
    {
        ret = UP;
    }
    if (x_pos > mWidth + offset && ret == STAY)
    {
        ret = LEFT;
    }
    if (y_pos < mHeight - offset && ret == STAY)
    {
        ret = DOWN;
    }
    return ret;
}

/**
 * @author David Donahue
 * @par Description:
 * Calculates whether or not not too attack, and if so where to attack
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return Location to attack and whether to attack
 */
direction NotSimpleAI::attack(const MapData &map, PositionData status)
{   
    direction ret = STAY;
    unsigned int i = 0;
    if (targetList.size() == 0) //No targets available
        return ret;
    
    while (i < targetList.size() && targetList[i].health < targetList[i].damage
            && !lineOfFire(targetList[i].x, targetList[i].y, status)){
        i++; //Find the first non killed target
    }

    if (targetList[i].health < targetList[i].damage || !(lineOfFire(targetList[i].x, targetList[i].y, status))){
        return ret; //No valid targets found
    }
    else if (status.game_x == targetList[i].x)
    {
        ret = (targetList[i].y > status.game_y) ? DOWN : UP;
    }
    else if (status.game_y == targetList[i].y)
    {
        ret = (targetList[i].x > status.game_x) ? RIGHT : LEFT;
    }
    else if (status.game_x > targetList[i].x) //to the upright or downright
    {
        ret = (targetList[i].y > status.game_y) ? DOWNLEFT : UPLEFT;
    }
    else
    {
        ret = (targetList[i].y > status.game_y) ? DOWNRIGHT : UPRIGHT;
    }
    if (spend == false)
        targetList[i].damage += myStats.tankDamage;
    return ret;
}


void NotSimpleAI::checkTargets(const MapData &map, PositionData status){
    int min_dist = map.width * map.height + 1; //Guaranteed to be greater than any real distance
    for (int x = 1; x <= map.width; ++x)
    {
        for (int y = 1; y <= map.height; ++y)
        {
            //If an enemy is encountered closer than previously encountered
            if (((map.tileMap[y][x].tank != nullptr && //if there is an actor at X, Y
                    map.tileMap[y][x].tank->id != status.id) || //And it is not you 
                    (map.tileMap[y][x].projectile != nullptr && 
                    map.tileMap[y][x].projectile->id != -status.id)) && //And it is not your projectile
                    calcDist(status.game_x, status.game_y, x, y) < min_dist) //And it is the closest one
            {
                //if (lineOfFire(x, y, status))
                //{
                    min_dist = calcDist(status.game_x, status.game_y, x, y);
                    if (map.tileMap[y][x].tank != nullptr){
                        targetList.emplace_back(min_dist, x, y, map.tileMap[y][x].tank->health, 0, map.tileMap[y][x].tank->id, false);
                    }else if(map.tileMap[y][x].projectile != nullptr){
                        targetList.emplace_back(min_dist, x, y, map.tileMap[y][x].projectile->health, 0, map.tileMap[y][x].projectile->id, true);
                    }
                //}

            }
        }
    }
    std::sort(targetList.begin(), targetList.end());
}

void NotSimpleAI::updateTargets(const MapData &map, PositionData status){
    int min_dist = map.width * map.height + 1; //Guaranteed to be greater than any real distance
    std::vector<target> tempTarget;
    for (int x = 1; x <= map.width; ++x)
    {
        for (int y = 1; y <= map.height; ++y)
        {
            //If an enemy is encountered closer than previously encountered
            if (((map.tileMap[y][x].tank != nullptr && //if there is an actor at X, Y
                    map.tileMap[y][x].tank->id != status.id) || //And it is not you 
                    (map.tileMap[y][x].projectile != nullptr && 
                    map.tileMap[y][x].projectile->id != -status.id)) && //And it is not your projectile
                    calcDist(status.game_x, status.game_y, x, y) < min_dist) //And it is the closest one
            {
                min_dist = calcDist(status.game_x, status.game_y, x, y);
                if (map.tileMap[y][x].tank != nullptr){
                    tempTarget.emplace_back(min_dist, x, y, map.tileMap[y][x].tank->health, 0, map.tileMap[y][x].tank->id, false);
                }else if(map.tileMap[y][x].projectile != nullptr){
                    tempTarget.emplace_back(min_dist, x, y, map.tileMap[y][x].projectile->health, 0, map.tileMap[y][x].projectile->id, true);
                }
            }
        }
    }
    if (tempTarget.size() > 0){
        for (unsigned int i = 0; i < tempTarget.size(); i++){
            for (unsigned int j = 0; j < targetList.size(); j++){
                if (tempTarget[i].x == targetList[j].x && tempTarget[i].y == targetList[j].y){
                    targetList.push_back(tempTarget[i]);
                    tempTarget[i].x = 0;
                    tempTarget[i].y = 0;
                }
            }
        }
        
        printf("Before sort:\n");
        for(auto & t : targetList){
        //    std::cout << t;
        }

        std::sort(targetList.begin(), targetList.end());
        printf("After sort:\n");
        for(auto & t : targetList){
        //    std::cout << t;
        }
    }
}

/**
 * @author David Donahue
 * @par Description:
 * Returns the attributes for the tank
 * @param[in] pointsAvailable - available points for the distribution
 * @return attributes of the tank
 */
attributes NotSimpleAI::setAttribute(int pointsAvailable, attributes baseStats)
{
    attributes tankAttributes;
    myStats = baseStats; 
    tankAttributes.tankAP += pointsAvailable;

    return tankAttributes;
}
/**
 * @author David Donahue
 * @par Description:
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] x1 - starting point x coordinate
 * @param[in] y1 - starting point y coordinate
 * @param[in] x2 - end point x coordinate
 * @param[in] y2 - end point y coordinate
 * @return distance to the target
 */
int NotSimpleAI::calcDist(int x1, int y1, int x2, int y2)
{
    int xDist = std::abs(x1 - x2);
    int yDist = std::abs(y1 - y2);
    int diagDist = 0;
    while (xDist > 0 && yDist > 0){
        yDist--;
        xDist--;
        diagDist++;
    }
    return xDist + yDist;
}

int NotSimpleAI::calcDist(direction dir, int dx, int dy, PositionData status){
    int dist = 9999, xoff=0, yoff=0, x, y;
    
    if (dir == UP || dir == UPLEFT || dir == UPRIGHT){yoff = -1;}
     else if (dir == DOWN || dir == DOWNLEFT || dir == DOWNRIGHT){yoff = 1;}
    if (dir == LEFT || dir == UPLEFT || dir == DOWNLEFT){xoff = -1;}
     else if (dir == RIGHT || dir == UPRIGHT || dir == DOWNRIGHT){xoff = 1;}
    x = xoff + status.game_x;
    y = yoff + status.game_y;

    if (x < 1 || y < 1 || (unsigned) x > heatMap[0].size() || (unsigned) y > heatMap.size()) //Not a valid move
        return dist;

    return calcDist(x, y, dx, dy);
}


int NotSimpleAI::spendAP(const MapData &map, PositionData status)
{
    updateMap(map, status);

    if (status.ap == myStats.tankAP){
        //printf("\n\nChecking Targets on start of turn.\n");
        targetList.clear();
        checkTargets(map, status);
        //printf("Number of targets found: %d.\n", (int) targetList.size());
    }else{
        updateTargets(map, status);
        //printf("Continuing turn.\n");
    }

    spend = true;
    direction tAttack = attack(map,status);
    spend = false;

    /*printf("Spend Map:\n");
    for (int i = 0; i < map.map.size(); i++){
    printf("%d ", map.map[i]);
    if (i % 30 == 29)
          printf("\n");
    }
    printf("X: %d, Y: %d\n", status.game_x, status.game_y);
    */

    if (tAttack != STAY) //Try and attack first
        return 2;

    spend = true;
    direction tMove = move(map,status);
    spend = false;

    if (tMove != STAY) //If there is nowhere to attack, move
        return 1;

    if (tAttack == STAY && tMove == STAY) //If there is nothing to do, end your turn
        return 3;

    return (status.ap > 1) ? 1 : 2;
}

void NotSimpleAI::updateMap(const MapData &map, PositionData status){
    if (firstTurn){
        int h = map.height + 1; //Add 1 so we can use 1 based coordinate system
        int w = map.width + 1;
        heatMap.resize(h); 
        for(int i = 0; i < (int) map.tileMap.size(); i++){
            heatMap[i].resize(w);
            for (int j = 0; j < (int) map.tileMap[i].size(); j++){
                heatMap[i][j] = 0;
            }
        }
        heatMap[1][1] = 100;
        heatMap[map.height][1] = 150;
        heatMap[map.height][map.width] = 250;
        heatMap[1][map.width] = 200;
        myStats.tankAP = status.ap;
        firstTurn = false;
    }
    for(int i = 1; i < (int) map.tileMap.size(); i++){
        for (int j = 1; j < (int) map.tileMap[i].size(); j++){
            if (heatMap[i][j] >= 0){
                heatMap[i][j]++;
            }
            if (map.tileMap[i][j].type == "Rock"){
                heatMap[i][j] = -50;
            }else if (map.tileMap[i][j].type == "Water"){
                heatMap[i][j] = -1000;
            }else if (map.tileMap[i][j].type == "Hedgehog"){
                heatMap[i][j] = -1000;
            }else if (map.tileMap[i][j].type == "Tree"){
                heatMap[i][j] = -25;
            }
        }
    }
    heatMap[status.game_y][status.game_x] = 0;   
    //std::cout << std::endl;
    //for(int i = 1; i < (int) map.tileMap.size(); i++){
    //    std::cout << std::endl;
    //    for (int j = 1; j < (int) map.tileMap[i].size(); j++){
    //            std::cout << heatMap[i][j] << "  ";
    //    }
    //}
}

bool NotSimpleAI::lineOfFire(int x, int y, PositionData status){
    int tx, ty;
    int myx = status.game_x;
    int myy = status.game_y;

    tx = myx - x;
    ty = myy - y;
    if (tx == 0 || ty == 0){ //It's directly verticle or horizontal to us
        return true;
    }
    if (tx == ty || tx == -ty){ //It's on a diagonal
        return true;
    }
    return false;
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new NotSimpleAI;
    }
}
#endif

std::ostream& operator<<(std::ostream& os, const NotSimpleAI::target& t)
{
    os << "Target: " << t.id << " (" << t.dist << '/' << t.x << '/' << t.y << '/' << t.health << '/' << t.damage << '/' << (t.bullet ? "Bullet)":"Tank)") << std::endl;
    return os;
}