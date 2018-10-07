//
// Created by 7401123 on 9/12/18.
//

#ifndef SRC_ATTACKDATA_H
#define SRC_ATTACKDATA_H


/*! \struct AttackData
    \brief Contains attack coordinates and damage value
*/
struct AttackData {
    int attack_x;  /*!<The x coordinate of the attack */
    int attack_y;   /*!<The y coordinate of the attack */
    int damage;     /*!<The damage value of the attack */
AttackData(int x, int y, int d) : attack_x(x), attack_y(y), damage(d) {}
    AttackData() {}
};


#endif //SRC_ATTACKDATA_H
