#include "catch.hpp"
#include <GameField.h>
#include <Actor.h>
#include <SimpleActor.h>


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
    Actor * a = new  SimpleActor;
    ActorInfo ai( a, 1, 1, 0, 0, 1);
    g.addActor(ai);
    REQUIRE(g.getActors()[0].act_p == a);
    delete a;
}
/*
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

TEST_CASE("cull() removes only actors with health of 0")
{
    GameField g;
    Actor a1 ("", 0, 0, 0, 0, 0);
    Actor a2 ("", 0, 0, 0, 1, 0);
    Actor a3 ("", 0, 0, 0, -1, 0);
    g.addActor(&a1);
    g.addActor(&a2);
    g.addActor(&a3);
    g.cull();
    REQUIRE(g.getActors().size() == 2);
}

TEST_CASE("Construct GameField with dimensions")
{
    GameField g (4, 5);
    REQUIRE ((g.getWidth() == 4 && g.getHeight() == 5));
}
TEST_CASE("getMap() returns valid map")
{
    GameField g (2, 2);
    std::vector<int> ref = {0, 0, 0, 0};
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("GameField constructs with actors")
{
    Actor a1 ("", 1, 0, 0, 0, 0);
    Actor a2 ("", 2, 1, 0, 0, 0);
    std::vector<Actor *> actorVect;
    actorVect.push_back(&a1);
    actorVect.push_back(&a2);
    GameField g (10, 10, actorVect);
    REQUIRE(g.getActors().size() == 2);
}
TEST_CASE("GameField correctly places actors on the map at construction")
{
    Actor a1 ("", 1, 1, 0, 0, 0);
    Actor a2 ("", 2, 0, 1, 0, 0);
    std::vector<Actor *> actorVect;
    actorVect.push_back(&a1);
    actorVect.push_back(&a2);
    GameField g (2, 2, actorVect);
    std::vector<int> ref = {0, 1, 2, 0};
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("GameField correctly places actors on the map when added")
{
    Actor a1 ("", 1, 1, 0, 0, 0);
    GameField g (2, 2);
    g.addActor(&a1);
    std::vector<int> ref = {0, 1, 0, 0};
    REQUIRE(g.getMap() == ref);
}
*/
