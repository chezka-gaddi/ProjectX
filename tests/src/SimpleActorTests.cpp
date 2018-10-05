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
