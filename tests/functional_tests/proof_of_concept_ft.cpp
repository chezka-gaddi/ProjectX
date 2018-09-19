#include <vector>
#include <catch.hpp>


SCENARIO("Proof of concept for FTs: Vector can be resized, and shrunk")
{
   GIVEN("A vector with some items")
   {
      std::vector<int> test(5);
      REQUIRE(test.size() == 5);
      

      WHEN("The Vector Grows")
      {
         test.resize(10);
         THEN("The size of the vector grows")
         {
            REQUIRE(test.size() == 10);
         }
      }

      WHEN("The Vector shrinks")
      {
         test.resize(2);
         THEN("The size of the vector grows")
         {
            REQUIRE(test.size() == 2);
         }
      }
   }
}
