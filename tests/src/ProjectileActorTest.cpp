#include "catch.hpp"
#include "../../src/ProjectileActor.h"

TEST_CASE("Vertical movement in move()")
{
	int test = 5;
	ProjectileActor shell;
	shell.endY = 5;	

	shell.move();
	REQUIRE (test == moveProjectile.new_y);
}

TEST_CASE("Horizontal movement in move()")
{
	int test = 5;
	ProjectileActor shell;
	shell.endX = 5;

	shell.move();
	REQUIRE (test == moveProjectile.new_x);
}

TEST_CASE("Diagonal movement (8,2) in move()")
{
	int testY = 4;
	int testX = 1;

	ProjectileActor shell;
	shell.endX = 2;
	shell.endY = 8;

	shell.move();
	REQUIRE (testX == moveProjectile.new_x &&
		 testY == moveProjectile.new_y);
}

TEST_CASE("Call attack() and ensure data is valid")
{
	ProjectileActor shell;
	
	shell.attack();
	REQUIRE (attackProjectile.attack_x == 1 &&
		 attackProjectile.attack_y == 1 &&
		 attackProjectile.damage == 1)
}

TEST_CASE("Test for getRange()")
{
	ProjectileActor shell;
	int test = ProjectileActor.getRange();

	REQUIRE (test = 10);
}

TEST_CASE("Test for getStartX()")
{
	ProjectileActor shell;
	int test = ProjectileActor.getStartX();

	REQUIRE (test == 0);
}

TEST_CASE("Test for getStartY()")
{
	ProjecileActor shell;
	int test = ProjectileActor.getStartY();

	REQUIRE(test == 0);
}

TEST_CASE("Test for getEndX()")
{
	ProjectileActor shell;
	int test = ProjectileActor.getEndX();
	
	REQUIRE(test == 0);
}

TEST_CASE("Test for getEndY()")
{
	ProjectileActor shell;
	int test = ProjectileActor.getEndY();

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
	shell.setStartX = 2;

	int test = shell.getStartX();

	REQUIRE(test == 2);
}

TEST_CASE("Test for setStartY(int startYUpdate)")
{
	ProjectileActor shell;
	shell.setStartY = 2;

	int test = shell.getStartY();
	
	REQUIRE(test == 2);
}

TEST_CASE("Test for setEndX(int endXUpdate)")
{
	ProjectileActor shell;
	shell.setStartX = 2;

	int test = shell.getEndX():

	REQUIRE(test == 2);
}

TEST_CASE("Test for setEndY(int endYUpdate)")
{
	ProjectileActor shell;
	shell.setStartX = 2;

	int test = shell.getEndY();
	
	REQUIRE(test == 2);
}



