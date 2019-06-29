#include "CamperAI.h"

CamperAI::CamperAI(void)
{
    // Tells the move function that we can go anywhere
}

CamperAI::~CamperAI(void)
{
}

direction CamperAI::move(const MapData &map, PositionData status)
{
    int x_pos = status.game_x;
    int y_pos = status.game_y;
    int median = map.height / 2;
    int median2 = map.width / 2;
    bool UP = false, DOWN = false, LEFT = false, RIGHT = false;

    direction retval = STAY;

    if((y_pos == 0 && x_pos == 0) ||
       (y_pos == map.height - 1 && x_pos == 0) ||
       (x_pos == map.width - 1 && y_pos == 0) ||
       (x_pos == map.width - 1 && y_pos == map.height - 1) ||
       (corner == true))
        return retval;
    if(y_pos <= median && y_pos - 1 >= 0 
                && (map.tileMap[y_pos-1][x_pos].type == "Empty" || 
                    map.tileMap[y_pos-1][x_pos].type == "Tree" ||
                    map.tileMap[y_pos-1][x_pos].type == "Bush"))
        UP = true;
    if(y_pos > median && (y_pos + 1 <= map.height - 1)
                && (map.tileMap[y_pos+1][x_pos].type == "Empty" || 
                map.tileMap[y_pos+1][x_pos].type == "Tree" ||
                map.tileMap[y_pos+1][x_pos].type == "Bush"))
                        
        DOWN = true;
    if(x_pos > median2 && (x_pos + 1 <= map.width - 1)
                && (map.tileMap[y_pos][x_pos+1].type == "Empty" || 
                    map.tileMap[y_pos][x_pos+1].type == "Tree" ||
                    map.tileMap[y_pos][x_pos+1].type == "Bush"))
        RIGHT = true;
    if(x_pos <= median2 && (x_pos - 1 >= 0)
                && (map.tileMap[y_pos][x_pos-1].type == "Empty" || 
                    map.tileMap[y_pos][x_pos-1].type == "Tree" ||
                    map.tileMap[y_pos][x_pos-1].type == "Bush"))
        LEFT = true;
    
    if (!UP && !DOWN && !RIGHT && !LEFT){
            retval = STAY;
            corner = true;
    }
    else if (UP && LEFT)
            retval = direction::UPLEFT;
    else if (UP && RIGHT)
            retval = direction::UPRIGHT;
    else if (UP)
            retval = direction::UP;
    else if (DOWN && LEFT)
            retval = direction::DOWNLEFT;
    else if (DOWN && RIGHT)
            retval = direction::DOWNRIGHT;
    else if (DOWN)
            retval = direction::DOWN;
    else if (LEFT)
            retval = direction::LEFT;
    else if (RIGHT)
            retval = direction::RIGHT;
    return retval;
}

direction CamperAI::attack(const MapData &map, PositionData status)
{
    int y_pos = status.game_y;
    int x_pos = status.game_x;
    int hmedian = map.height / 2;
    int wmedian = map.width / 2;
    direction retval;

    if(y_pos >= hmedian && x_pos <= wmedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retval = UPRIGHT;
            break;
        case 2:
            retval = RIGHT;
            break;
        default:
            retval = UP;
            break;
        }
    }
    else if(y_pos < hmedian && x_pos <= wmedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retval = DOWNRIGHT;
            break;
        case 2:
            retval = RIGHT;
            break;
        default:
            retval = DOWN;
            break;
        }
    }
    else if(y_pos >= hmedian && x_pos > wmedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retval = UPLEFT;
            break;
        case 2:
            retval = LEFT;
            break;
        default:
            retval = UP;
            break;
        }
    }
    else if(y_pos < hmedian && x_pos > wmedian)
    {
        switch (attacks[turn])
        {
        case 1:
            retval = DOWNLEFT;
            break;
        case 2:
            retval = LEFT;
            break;
        default:
            retval = DOWN;
            break;
        }
    }

    return retval;
}

attributes CamperAI::setAttribute(int pointsAvailable, attributes baseStats)
{
    attributes retval;

    retval.tankHealth = pointsAvailable;

    return retval;
}

int CamperAI::spendAP(const MapData &map, PositionData status)
{
    if (maxAp == 0)
        maxAp = status.ap;
    if (maxAp == status.ap){
        turn = 0;
        for (int i = 0; i < 6; i++)
                attacks[i] = rand() % 3;
    }
    else
        turn++;
    if (move(map, status) != STAY)
        return 1;
    return 2; // Attack
}



#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new CamperAI;
    }
}
#endif
