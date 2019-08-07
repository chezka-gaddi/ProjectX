/**
 * @file
 * @brief Test the functionalities of Gizmo tank.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Gizmo.h"
#include "map/MapData.h"
#include "structures/PositionData.h"
#include "structures/direction.h"
#include "structures/attributes.h"



TEST_CASE("Test Set Stats")
{
    attributes base = attributes(2, 1, 2, 5, 3);
    Gizmo tank = Gizmo();
    attributes test = tank.setAttribute(0, base);
    REQUIRE(test.tankHealth == 2);
    REQUIRE(test.tankDamage == 1);
    REQUIRE(test.tankAP == 2);
    REQUIRE(test.tankRadar == 5);
    REQUIRE(test.tankAmmo == 3);
}


TEST_CASE("Test SpendAP")
{
    PositionData pos = PositionData(0, 1, 0, 0);
    MapData map = MapData();
    Gizmo tank = Gizmo();
    int test = tank.spendAP(map, pos);
    REQUIRE(test == 0);
}


TEST_CASE("Test Movement")
{
    PositionData pos = PositionData(0, 1, 0, 0);
    MapData map = MapData();
    Gizmo tank = Gizmo();
    direction test = tank.move(map, pos);
    REQUIRE(test == UP);
}


TEST_CASE("Test Attack")
{
    PositionData pos = PositionData(0, 1, 0, 0);
    MapData map = MapData();
    Gizmo tank = Gizmo();
    direction test = tank.attack(map, pos);
    REQUIRE(test == UP);
}
