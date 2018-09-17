#include "catch.hpp"
#include "../../src/Actor.h"
#include <string>
#define testing

// Testing setters and default constructor
TEST_CASE("Calling getName() member function and checking construstor")
{
     Actor actor;
     string test = actor.getName();
     REQUIRE(test == "");
}

TEST_CASE("Calling getId() member function and checking construstor")
{
     Actor actor;
     int test = actor.getId();
     REQUIRE(test == 0);
}

TEST_CASE("Calling getFieldX() member function and checking construstor")
{
     Actor actor;
     int test = actor.getFieldX();
     REQUIRE(test == 0);
}

TEST_CASE("Calling getFieldY() member function and checking construstor")
{
     Actor actor;
     int test = actor.getFieldY();
     REQUIRE(test == 0);
}

TEST_CASE("Calling getHealth() member function and checking construstor")
{
     Actor actor;
     int test = actor.getHealth();
     REQUIRE(test == 0);
}

TEST_CASE("Calling getDamage() member function and checking construstor")
{
     Actor actor;
     int test = actor.getDamage();
     REQUIRE(test == 0);
}

// Testing setters
TEST_CASE("Changing the value in name and using	the setHealth() function to change it")
{
     Actor actor;
     string test; 
  
     actor.setName("George");
     test = actor.getName();
     REQUIRE(test == "George");
}

TEST_CASE("Changing the value in id and using the setId() function to change it")
{
     Actor actor;
     int test; 
  
     actor.setId(91);
     test = actor.getId();
     REQUIRE(test == 91);
}

TEST_CASE("Changing the value in field_x and using the setFieldX() function to change it")
{
     Actor actor;
     int test; 

     actor.setFieldX(32);
     test = actor.getFieldX();
     REQUIRE(test == 32);
}

TEST_CASE("Changing the value in field_y and using the setFieldY() function to change it")
{
     Actor actor;
     int test;

     actor.setFieldY(67);
     test = actor.getFieldY();
     REQUIRE(test == 67);
}

TEST_CASE("Changing the value in health and using the setHealth() function to change it")
{
     Actor actor;
     int test;

     actor.setHealth(45);
     test = actor.getHealth();
     REQUIRE(test == 45);
}

TEST_CASE("Changing the value in damage and using the setDamage() function to change it")
{
     Actor actor;
     int test;

     actor.setDamage(72);
     test = actor.getDamage();
     REQUIRE(test == 72);
}
