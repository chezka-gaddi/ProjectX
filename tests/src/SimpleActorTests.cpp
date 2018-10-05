#include "catch.hpp"
#include <SimpleActor.h>
#include <Actor.h>


TEST_CASE("SimpleActor constructs correctly")
{
    SimpleActor a;
    REQUIRE(sizeof(a) > 0);
}
TEST_CASE("default SimpleActor.move() returns up")
{
    SimpleActor* a = new SimpleActor; //Apparently the constructor does not run when delcaring directly.
    MapData m;
    PositionData p;
    REQUIRE(a->move(m,p) == up);
    delete a;
}
TEST_CASE("default SimpleActor.attack() attacks 0,0 with 0 damage")
{
    SimpleActor* a = new SimpleActor;
    MapData m;
    PositionData p;
    AttackData result;
    result = a->attack(m,p);
    REQUIRE(( result.attack_x == 0 && result.attack_y == 0 && result.damage == 0));
    delete a;
}
TEST_CASE("SimpleActor moves in the direction specified at construction")
{
    SimpleActor* a = new SimpleActor(down, 0);
    MapData m;
    PositionData p;
    REQUIRE(a->move(m,p) == down);
    delete a;
}
TEST_CASE("SimpleActor.attack() attacks specified point with specified damage")
{
    SimpleActor* a = new SimpleActor(stay, 0);
    MapData m;
    PositionData p;
    AttackData result;
    a->setAttack(1, 1, 1);
    result = a->attack(m,p);
    REQUIRE(result.attack_x == 1);
    REQUIRE( result.attack_y == 1);
    REQUIRE( result.damage == 1 );
    delete a;
}
TEST_CASE("SimpleActor.setMove() changes the return of SimpleActor.move()")
{
    SimpleActor* a = new SimpleActor(up, 0);
    MapData m;
    PositionData p;
    a->setMove(down);
    REQUIRE(a->move(m,p) == down);
    delete a;
}
