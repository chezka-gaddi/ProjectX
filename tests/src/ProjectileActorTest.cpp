#include "catch.hpp"
#include "ProjectileActor.h"
#include "PositionData.h"
#include "MapData.h"

TEST_CASE("Move projectile up in move()")
{
    int testY = 0;
    int testX = 1;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;
    status.field_x = 1;
    status.field_x = 1;
    shell.setEndY(0);
    shell.setEndX(1);

    movement = shell.move(map, status);
    REQUIRE (testY == movement.new_y && testX == movement.new_x);
}

TEST_CASE("Move projectile to the right in move()")
{
    int testX = 2;
    int testY = 1;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;
    status.field_x = 1;
    status.field_y = 1;
    shell.setEndX(2);
    shell.setEndY(1);

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("Move projectile down in move()")
{
    int testX = 1;
    int testY = 2;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;
    status.field_x = 1;
    status.field_y = 1;
    shell.setEndX(1);
    shell.setEndY(2);

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("(Move projectile left in move()")
{
    int testX = 1;
    int testY = 1;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;

    status.field_x = 1;
    status.field_y = 1;
    shell.setEndX(0);
    shell.setEndY(1);

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("Move projectile up and right in move()")
{
    int testY = 0;
    int testX = 2;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;

    shell.setEndX(2);
    shell.setEndY(0);
    status.field_x = 1;
    status.field_y = 1;

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("Move projectile left and up in move()")
{
    int testY = 0;
    int testX = 0;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;

    shell.setEndX(0);
    shell.setEndY(0);
    status.field_x = 1;
    status.field_y = 1;

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("Move projectile down and right in move()")
{
    int testY = 2;
    int testX = 2;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;

    status.field_x = 1;
    status.field_y = 1;
    shell.setEndX(2);
    shell.setEndY(2);

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("Move projectile down and left in move()")
{
    int testY = 2;
    int testX = 0;
    ProjectileActor shell;
    PositionData status;
    MapData map;
    MoveData movement;

    status.field_x = 1;
    status.field_y = 1;
    shell.setEndX(0);
    shell.setEndY(2);

    movement = shell.move(map, status);
    REQUIRE (testX == movement.new_x && testY == movement.new_y);
}

TEST_CASE("Call attack() and ensure data is valid")
{
    ProjectileActor shell;

    shell.attack();
    REQUIRE (shell.attack_x == 1 &&
             shell.attack_y == 1 &&
             shell.damage == 1)
}

TEST_CASE("Test for getRange()")
{
    ProjectileActor shell;
    int test = shell.getRange();

    REQUIRE (test == 10);
}

TEST_CASE("Test for getStartX()")
{
    ProjectileActor shell;
    int test = shell.getStartX();

    REQUIRE (test == 0);
}

TEST_CASE("Test for getStartY()")
{
    ProjectileActor shell;
    int test = shell.getStartY();

    REQUIRE(test == 0);
}

TEST_CASE("Test for getEndX()")
{
    ProjectileActor shell;
    int test = shell.getEndX();

    REQUIRE(test == 0);
}

TEST_CASE("Test for getEndY()")
{
    ProjectileActor shell;
    int test = shell.getEndY();

    REQUIRE(test == 0);
}

TEST_CASE("Test for setRange(int range)")
{
    ProjectileActor shell;
    shell.setRange(5);

    int test = shell.getRange();

    REQUIRE(test == 5);
}

TEST_CASE("Test for setStartX(int startXUpdate)")
{
    ProjectileActor shell;
    shell.setStartX(2);

    int test = shell.getStartX();

    REQUIRE(test == 2);
}

TEST_CASE("Test for setStartY(int startYUpdate)")
{
    ProjectileActor shell;
    shell.setStartY(2);

    int test = shell.getStartY();

    REQUIRE(test == 2);
}

TEST_CASE("Test for setEndX(int endXUpdate)")
{
    ProjectileActor shell;
    shell.setEndX(2);

    int test = shell.getEndX();

    REQUIRE(test == 2);
}

TEST_CASE("Test for setEndY(int endYUpdate)")
{
    ProjectileActor shell;
    shell.setEndY(2);

    int test = shell.getEndY();

    REQUIRE(test == 2);
}



