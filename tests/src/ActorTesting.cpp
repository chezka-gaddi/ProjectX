#include "catch.hpp"
#include "../../src/Actor.h"
#include <string>
#include <iostream>

// Testing setters and default constructor
TEST_CASE("Calling getName() member function and checking construstor")
{
     Actor actor;
     string test = actor.getName();
     REQUIRE(test == "");
}

TEST_CASE("Calling getId() member function and checking construstor")
{
     std::cout << "Made it here" << endl;
     Actor actor;
     int test = actor.getId();
     REQUIRE(test == 0);
}

TEST_CASE("Calling getFieldX() member function and checking construstor")
{
     Actor actor;
     int test = actor.getFieldX();
     REQUIRE(test == -1);
}

TEST_CASE("Calling getFieldY() member function and checking construstor")
{
     Actor actor;
     int test = actor.getFieldY();
     REQUIRE(test == -1);
}

TEST_CASE("Calling getHealth() member function and checking construstor")
{
     Actor actor;
     int test = actor.getHealth();
     REQUIRE(test == -1);
}

TEST_CASE("Calling getDamage() member function and checking construstor")
{
     Actor actor;
     int test = actor.getDamage();
     REQUIRE(test == 1);
}

// Testing constructor with given values
TEST_CASE("Test Constructor the will inialize all member variables from input variables")
{
     string nameTest = "DEFAULT";
     int testArry[5] = { 67 , 98 , 34 , 21 , 93 };
     Actor actor("DEFAULT", 67, 98, 34, 21, 93);

     REQUIRE(nameTest == actor.getName());
     REQUIRE(testArry[0] == actor.getId()); 
     REQUIRE(testArry[1] == actor.getFieldX());
     REQUIRE(testArry[2] == actor.getFieldY());
     REQUIRE(testArry[3] == actor.getHealth());
     REQUIRE(testArry[4] == actor.getDamage());
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
