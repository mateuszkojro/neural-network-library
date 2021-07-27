#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include <catch2/catch.hpp>

unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

#include "Matrix.h"

TEST_CASE("Matrix addition is correct", "[Matrix]") {
  Matrix A = {{1,2}, {3,4}};
  Matrix B = {{1,1}, {1,1}};

  Matrix expected = {{2,3},{4,5}};

  REQUIRE(expected == (A + B));
}