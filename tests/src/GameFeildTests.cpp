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
    
}

TEST_CASE("findActorByCoord() works with no actors")
{
    GameField g;
    REQUIRE(g.findActorsByCoord(0,0).size() == 0);
}

TEST_CASE("findActorByCoord() returns correct actors")
{
    GameField g;
    ActorInfo a1 (NULL, 1, 1, 0, 0, 1);
    ActorInfo a2 (NULL, 2, 1, 0, 0, 1);
    ActorInfo a3 (NULL, 3, 1, 1, 1, 1);
    
    
    
    g.addActor(a1);
    g.addActor(a2);
    g.addActor(a3);

    std::vector<ActorInfo> hits = g.findActorsByCoord(0,0);
    //make sure that 2 actors are returned and they are the right ones
    REQUIRE((hits.size() == 2
             && (hits[0] == a1 || hits[1] == a1)
             && (hits[0] == a2 || hits[1] == a2) ));
    
}

TEST_CASE("cull() removes only actors with health of 0")
{
    GameField g;
    ActorInfo a1 (NULL, 1, 0, 0, 0, 0);
    ActorInfo a2 (NULL, 0, 0, 0, 0, 0);
    ActorInfo a3 (NULL, 0, 0, 0, 0, 0);
    ActorInfo a4 (NULL, -1, 0, 0, 0, 0);
    g.addActor(a1);
    g.addActor(a2);
    g.addActor(a3);
    g.addActor(a4);
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
    Actor * a1 = new SimpleActor;
    Actor * a2 = new SimpleActor;
    std::vector<ActorInfo> actors(2);
    actors[0].act_p = a1;
    actors[1].act_p = a2;
    GameField g (10, 10, actors);
    REQUIRE(g.getActors().size() == 2);
}

TEST_CASE("GameField correctly places actors on the map at construction")
{
    std::vector<ActorInfo> actorVect(2);
    actorVect[0].act_p = NULL;
    actorVect[0].id = 1;
    actorVect[0].x = 1;
    actorVect[0].y = 0;
    actorVect[0].health = 1;
    actorVect[1].act_p = NULL;
    actorVect[1].id = 2;
    actorVect[1].x = 0;
    actorVect[1].y = 1;
    actorVect[1].health = 1;
    GameField g (2, 2, actorVect);
    std::vector<int> ref = {0, 1, 2, 0};
    REQUIRE(g.getMap() == ref);
}

TEST_CASE("GameField correctly places actors on the map when added")
{
    Actor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 1, 0, 1);
    GameField g (2, 2);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actor moves when nextTurn() is called")
{
    Actor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 1, 1, 1);
    GameField g (2, 2);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors are prevented from moving off the map")
{
    Actor * a = new SimpleActor;
    ActorInfo newAI(a, 2, 1, 1, 0, 1);
    GameField g (2, 2);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors can attack the desired space on nextMove() and dead Actors are culled")
{
    Actor * a1 = new SimpleActor(STAY, 1);
    Actor * a2 = new SimpleActor(UP, 0);
    ActorInfo newAI1(a1, 1, 1, 0, 2, 1);
    ActorInfo newAI2(a2, 1, 1, 0, 0, 2);
    GameField g (1, 3);
    g.addActor(newAI1);
    g.addActor(newAI2);
    std::vector<int> ref = {0, 0, 1};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors move until their range is depleted")
{
    Actor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 0, 3, 1, 2);
    GameField g (1,4);
    g.addActor(newAI);
    std::vector<int> ref = {0, 1, 0, 0};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors spawn and move projectiles on attack")
{
    Actor * a = new SimpleActor(STAY, 1);
    ActorInfo newAI(a, 1, 1, 0, 7, 1, 0);
    GameField g (1, 8);
    g.addActor(newAI);
    std::vector<int> ref = {0, -1, 0, 0, 0, 0, 0, 1};
    g.nextTurn();
    REQUIRE(g.getMap() == ref);
}
TEST_CASE("Actors take 1 point of damage from the walls of the arena")
{
    Actor * a = new SimpleActor(UP, 0);
    ActorInfo newAI(a, 2, 1, 0, 0, 1, 1);
    GameField g (1, 1);
    g.addActor(newAI);
    g.nextTurn();
    REQUIRE(g.getActors().back().health == 1); //check for damage from the wall
}

TEST_CASE("Actors are culled and do not move after collision")
{
    Actor * t1 = new SimpleActor(STAY, 1); //attacker tank
    Actor * t2 = new SimpleActor(STAY, 0); //target tanks
    Actor * t3 = new SimpleActor(STAY, 0);

    ActorInfo t1i (t1, 1, 1, 0, 3, 1);
    ActorInfo t2i (t2, 1, 1, 0, 1, 2);
    ActorInfo t3i (t3, 1, 1, 0, 0, 3); //Initial map of {3, 2, 0 ,1}

    std::vector<ActorInfo> tvect(3);
    tvect[0] = t1i;
    tvect[1] = t2i;
    tvect[2] = t3i;

    GameField g (1, 4, tvect);

    g.nextTurn(); //tank 1 will fire up at the other tanks

    std::vector<int> ref = {3, 0, 0, 1}; //Tank 2 hit, Tank 3 and 1 remain
    REQUIRE(g.getMap() == ref);

}


TEST_CASE("Collision is checked when firing point-blank")
{
    Actor * t1 = new SimpleActor(STAY, 1); //attacker tank
    Actor * t2 = new SimpleActor(STAY, 0); //target tanks
    Actor * t3 = new SimpleActor(STAY, 0);

    ActorInfo t1i (t1, 1, 1, 0, 2, 1);
    ActorInfo t2i (t2, 1, 1, 0, 1, 2);
    ActorInfo t3i (t3, 1, 1, 0, 0, 3); //Initial map of {3, 2, 1}

    std::vector<ActorInfo> tvect(3);
    tvect[0] = t1i;
    tvect[1] = t2i;
    tvect[2] = t3i;

    GameField g (1, 3, tvect);

    g.nextTurn(); //tank 1 will fire up at the other tanks, point blank on t2

    std::vector<int> ref = {3, 0, 1}; //Tank 2 hit, Tank 3 and 1 remain

    //failure looks like {0, 2, 1}
    REQUIRE(g.getMap() == ref);

}

TEST_CASE("Projectiles self destruct after reaching their target")
{

    SimpleActor * a = new SimpleActor(STAY, 1);
    a->setAttack(0, 10, 1);
    ActorInfo newAI(a, 1, 1, 0, 19, 1, 0);
    GameField g (1, 20);
    g.addActor(newAI);
    std::vector<int> ref (20);
    ref[19] = 1;
    g.nextTurn();
    a->setAttack (0,0,0);
    g.nextTurn();

    REQUIRE(g.getMap() == ref);

}

TEST_CASE("Actor shot counter incremented on attacking")
{
    SimpleActor * a = new SimpleActor(STAY, 1);
    ActorInfo newAI(a, 1, 1, 0, 1, 1, 0);
    GameField g (1, 2);
    g.addActor(newAI);
    g.nextTurn();

    REQUIRE(g.getActors().at(0).shots == 1);
}
TEST_CASE("Actor hit counter incremented on hiting an enemy")
{
    SimpleActor * a1 = new SimpleActor(STAY, 1);
    SimpleActor * a2 = new SimpleActor(STAY, 0);

    ActorInfo AI1(a1, 10, 1, 0, 1, 1, 0);
    ActorInfo AI2(a2, 10, 1, 0, 0, 2, 0);

    GameField g (1, 2);
    g.addActor(AI1);
    g.addActor(AI2);
    g.nextTurn();

    REQUIRE(g.actorInfoById(1).hits == 1);
}

TEST_CASE("GameField.actorInfoById returns a null actor (All fields 0) when ID not found")
{
    GameField g;
    REQUIRE(g.actorInfoById(2) == ActorInfo (0,0,0,0,0,0));
}
TEST_CASE("GameField.actorInfoById returns a reference to the desired actor")
{
    GameField g;
    SimpleActor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 0, 0, 1, 0);

    g.addActor(newAI);

    REQUIRE(g.actorInfoById(1) == newAI);
}
TEST_CASE("GameField.actorInfoById references can be used to update actors on the field")
{
    GameField g;
    SimpleActor * a = new SimpleActor;
    ActorInfo newAI(a, 1, 1, 0, 0, 1, 0);

    g.addActor(newAI);

    g.actorInfoById(1).health = 10;
    newAI.health = 10;

    REQUIRE(g.actorInfoById(1) == newAI);
}


TEST_CASE("Obstacles can be added to the gamefield")
{
    GameField g; //10x10 empty gamefield

    REQUIRE(g.obstacleAt(1, 1) == false); //make sure the space starts empty
    
    g.addObstacle(1, 1);

    REQUIRE(g.obstacleAt(1, 1) == true); //check to make sure the obstacle was added
}

TEST_CASE("Obstacles can be removed from the gamefield")
{
    GameField g; //10x10 empty gamefield
    
    g.addObstacle(1, 1);
    g.removeObstacle(1, 1);

    REQUIRE(g.obstacleAt(1, 1) == false); //check to make sure the obstacle was added
}
TEST_CASE("Actors take 1 point of damage from hitting obstacles")
{
    Actor * a = new SimpleActor(UP, 0);
    ActorInfo newAI(a, 2, 1, 0, 2, 1, 1);
    GameField g (1, 3);
    g.addActor(newAI);
    g.addObstacle(0, 1);
    g.nextTurn();
    REQUIRE(g.actorInfoById(1).health== 1); //check for damage from the obstacle
}
TEST_CASE("Actors do not take damage when shooting an obstacle point-blank")
{
    Actor * a = new SimpleActor(STAY, 1);
    ActorInfo newAI(a, 2, 1, 0, 1, 1, 1);
    GameField g (1, 2);
    g.addActor(newAI);
    g.addObstacle(0, 0);
    g.nextTurn();
    REQUIRE(g.actorInfoById(1).health== 2); //check for damage from the obstacle
}
TEST_CASE("Actors take 1 point of damage from the wall trying to move up/left")
{
    Actor *a = new SimpleActor(UPLEFT, 0);
    ActorInfo newAI(a, 2, 1, 1, 0, 1, 1); // set up to hit upper wall
    GameField g (2, 2);
    g.addActor(newAI);
    g.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    Actor *a2 = new SimpleActor(UPLEFT, 0);
    ActorInfo newAI2(a2, 2, 1, 0, 1, 1, 1); // setup to hit left wall
    GameField g2 (2, 2);
    g.addActor(newAI2);
    g.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
}
TEST_CASE("Actor moves diagonal up/left and changes position")
{
    Actor *a = new SimpleActor(UPLEFT, 0);
    ActorInfo newAI(a, 2, 1, 1, 1, 1, 1);
    GameField g (2, 2);
    g.addActor(newAI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 0);
    REQUIRE(g.getActors().back().y == 0);
}
TEST_CASE("Actor moves diagonal up/right and changes position")
{
    Actor *a = new SimpleActor(UPRIGHT, 0);
    ActorInfo AI(a, 2, 1, 0, 1, 1, 1);
    GameField g (2, 2);
    g.addActor(AI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 1);
    REQUIRE(g.getActors().back().y == 0);
}
TEST_CASE("Actors moves diagonal up/right into a wall and takes damage")
{
    Actor *a = new SimpleActor(UPRIGHT, 0);
    Actor *a2 = new SimpleActor(UPRIGHT, 0);
    ActorInfo AI(a, 2, 1, 1, 1, 1, 1); // setup to hit right wall
    ActorInfo AI2(a2, 2, 1, 0, 0, 1, 1); // setup to hit upper wall
    GameField g (2, 2);
    GameField g2 (2, 2);
    g.addActor(AI);
    g2.addActor(AI2);
    g.nextTurn();
    g2.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    REQUIRE(g2.getActors().back().health == 1);
}
TEST_CASE("Actor moves diagonal down/left and changes position")
{
    Actor *a = new SimpleActor(DOWNLEFT, 0);
    ActorInfo AI(a, 2, 1, 1, 0, 1, 1);
    GameField g (2, 2);
    g.addActor(AI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 0);
    REQUIRE(g.getActors().back().y == 1);
}
TEST_CASE("Actor moves diagonal down/left and collides with wall")
{    
    Actor *a = new SimpleActor(DOWNLEFT, 0);
    Actor *a2 = new SimpleActor(DOWNLEFT, 0);
    ActorInfo AI(a, 2, 1, 0, 0, 1, 1); // setup to hit left wall
    ActorInfo AI2(a2, 2, 1, 0, 1, 1, 1); // setup to hit lower wall
    GameField g (2, 2);
    GameField g2 (2, 2);
    g.addActor(AI);
    g2.addActor(AI2);
    g.nextTurn();
    g2.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    REQUIRE(g2.getActors().back().health == 1);
}
TEST_CASE("Actor moves diagonal down/right and changes position")
{
    
    Actor *a = new SimpleActor(DOWNRIGHT, 0);
    ActorInfo AI(a, 2, 1, 0, 0, 1, 1);
    GameField g (2, 2);
    g.addActor(AI);
    g.nextTurn();
    REQUIRE(g.getActors().back().x == 1);
    REQUIRE(g.getActors().back().y == 1);
}
TEST_CASE("Actor moves diagonal down/right and collides with wall")
{

    Actor *a = new SimpleActor(DOWNRIGHT, 0);
    Actor *a2 = new SimpleActor(DOWNRIGHT, 0);
    ActorInfo AI(a, 2, 1, 1, 0, 1, 1); // setup to hit right wall
    ActorInfo AI2(a2, 2, 1, 0, 1, 1, 1); // setup to hit lower wall
    GameField g (2, 2);
    GameField g2 (2, 2);
    g.addActor(AI);
    g2.addActor(AI2);
    g.nextTurn();
    g2.nextTurn();
    REQUIRE(g.getActors().back().health == 1);
    REQUIRE(g2.getActors().back().health == 1);
}
