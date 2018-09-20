#include "catch.hpp"
#include "../../src/GameField.h"
#include "../../src/Actor.h"


TEST_CASE("Instantiate GameField")
{
    GameField g;
    REQUIRE(sizeof(g) > 0);
}

TEST_CASE("Get Turn Count")
{
    GameField g;
    REQUIRE(g.getTurnCount() == 0);
}

TEST_CASE("nextTurn increments turnCount")
{
    GameField g;
    g.nextTurn();
    REQUIRE(g.getTurnCount() == 1);
}
TEST_CASE("addActor adds an actor to actors")
{
    GameField g;
    Actor * a;
    a = new (nothrow) Actor;
    g.addActor(a);
    REQUIRE(g.getActors()[0] == a);
    delete a;
}
//Actor(string newName, int newId, int newFieldX, int newFieldY, int newHealth, int newDamage);
