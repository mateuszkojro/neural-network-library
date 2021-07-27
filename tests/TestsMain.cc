#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "Matrix.h"
#include <catch2/catch.hpp>

TEST_CASE("Matrix addition is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};
  Matrix B = {{1, 1}, {1, 1}};

  Matrix expected = {{2, 3}, {4, 5}};

  REQUIRE(expected == (A + B));
}

TEST_CASE("Matrix multiplication is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};
  Matrix B = {{1, 2}, {3, 4}};

  Matrix expected = {{7, 10}, {15, 22}};

  REQUIRE(expected == (A * B));
}

TEST_CASE("Matrix subtraction is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};
  Matrix B = {{1, 1}, {1, 1}};

  Matrix expected = {{0, 1}, {2, 3}};

  REQUIRE(expected == (A - B));
}

TEST_CASE("Multiplying by scalar is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};

  Matrix expected = {{2, 4}, {6, 8}};

  REQUIRE(expected == (A * 2));
}

TEST_CASE("Matrix transpose is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};

  Matrix expected = {{1, 3}, {2, 4}};

  A.Transpose().Print();

  REQUIRE(expected == (A.Transpose()));
}
