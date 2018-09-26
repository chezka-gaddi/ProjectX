#include "catch.hpp"
#include <ProjectileActor.h>
/*
TEST_CASE("Vertical movement in move()")
{
	int test = 5;
	ProjectileActor shell;
	shell.setEndY(5);	

	shell.move();
	REQUIRE (test == shell.getNewY());
}

TEST_CASE("Horizontal movement in move()")
{
	int test = 5;
	ProjectileActor shell;
	shell.setEndX(5);

	shell.move();
	REQUIRE (test == shell.getNewX());
}

TEST_CASE("Diagonal movement (8,2) in move()")
{
	int testY = 4;
	int testX = 1;

	ProjectileActor shell;
	shell.setEndX(2);
	shell.setEndY(8);

	shell.move();
	REQUIRE (testX == shell.getNewX() &&
		 testY == shell.getNewY());
}

TEST_CASE("Call attack() and ensure data is valid")
{
	ProjectileActor shell;
	
	shell.attack();
	REQUIRE (shell.attack_x == 1 &&
		 shell.attack_y == 1 &&
		 shell.damage == 1)
}
*/
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



