#include "PongAI.h"

PongAI::PongAI(void)
{
    // Tells the move function that we can go anywhere
    std::fill(nogo_map.begin(), nogo_map.end(), true);
}

PongAI::~PongAI(void)
{
    // Intentionally Left Empty
}

direction PongAI::move(MapData map, PositionData status)
{
    std::cout << __func__ << std::endl;
    int x_pos = status.game_x;
    int y_pos = status.game_y;

    int map_x_reference = map.width * y_pos + x_pos;

    direction retval = DOWN;
    if(y_pos == 0)
        retval = DOWN;
    else if(y_pos == map.height - 1)
        retval = UP;
    else if(LastDir == UP)
        retval = DOWN;
    else if(LastDir == DOWN)
        retval = UP;
    else
        retval = UP;

    if(next(map.obstacleMap, retval, map, status) != true || next(nogo_map, retval, map, status) != true)
    {
        if(map.obstacleMap.at(map_x_reference - 1) == false 
                && x_pos != 0)
            retval = LEFT;
        else if ( map.obstacleMap.at (map_x_reference + 1) == false
                && x_pos != map.width -1)
            retval = RIGHT;

        else if(retval == UP)
        {
            // We cant go up here, mark it on our map as a nogo
            nogo_map.at(map_x_reference) = false;
            retval = DOWN;
        }
        else if(retval == DOWN)
        {
            // We cant go up here, mark it on our map as a nogo
            nogo_map.at(map_x_reference) = false;
            retval = UP;
        }
    }
    LastDir = retval;

    return retval;

}

direction PongAI::attack(MapData map, PositionData status)
{
    std::cout << __func__ << std::endl;
    int x_pos = status.game_x;
    int median = map.width / 2;
    direction retval;

    if(x_pos >= median)
        retval = LEFT;
    else
        retval = RIGHT;

    return retval;
}

attributes PongAI::setAttribute(int pointsAvailable)
{
    std::cout << __func__ << std::endl;
    attributes retval;

    retval.tankRange = pointsAvailable;

    return retval;
}

int PongAI::spendAP(MapData map, PositionData status)
{
    std::cout << __func__ << std::endl;
    if(status.ap == 1)
        return 2; // Attack
    else
        return 1; // Move
}


bool PongAI::next(std::vector<bool> target_map, direction attempted_move, MapData map, PositionData status)
{
    
    int x_pos = status.game_x;
    int y_pos = status.game_y;

    int map_x_reference = 0;
    
    if (attempted_move == UP) 
        map_x_reference = (map.width * y_pos - 1) + x_pos;

    else
        map_x_reference = (map.width * y_pos + 1) + x_pos;

    return target_map.at(map_x_reference);
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new PongAI;
    }
}
#endif
