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
TEST_CASE("findActorByCoord() works with no actors")
{
    GameField g;
    REQUIRE(g.findActorsByCoord(0,0).size() == 0);
}
TEST_CASE("findActorByCoord() returns correct actors")
{
    GameField g;
    Actor a1("", 0, 0, 0, 0, 0);
    Actor a2("", 0, 0, 0, 0, 0);
    Actor a3("", 0, 1, 1, 0, 0);
    std::vector<Actor *> hits;
    
    g.addActor(&a1);
    g.addActor(&a2);
    g.addActor(&a3);

    hits = g.findActorsByCoord(0,0);
    //make sure that 2 actors are returned and they are the right ones
    REQUIRE((hits.size() == 2
             && (hits[0] == &a1 || hits[1] == &a1)
             && (hits[0] == &a2 || hits[1] == &a2) ));
    
}


