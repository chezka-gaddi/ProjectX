//
// Created by 7401123 on 9/12/18.
//

#include "AttackData.h"

/**
 * @author David Donahue
 * @par Description:
 * overload of the == operator to compare 2 AttackData structs
 * 
 * @param[in] lhs - left hand operand
 * @param[in] rhs - right had operand
 * @return true if the AttackDatas' fields are equal
 */
bool operator==(AttackData lhs, AttackData rhs)
{
    return (lhs.attack_x == rhs.attack_x && lhs.attack_y == rhs.attack_y && lhs.damage == rhs.damage);
}
