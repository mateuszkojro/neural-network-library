#include "Matrix.h"
#include "catch2/catch.hpp"

TEST_CASE("Matrix addition is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};
  Matrix B = {{1, 1}, {1, 1}};

  Matrix expected = {{2, 3}, {4, 5}};

  REQUIRE(expected == (A + B));
}

TEST_CASE("Square matrix multiplication is correct", "[Matrix]") {
  Matrix A = {{1, 2}, {3, 4}};
  Matrix B = {{1, 2}, {3, 4}};

  Matrix expected = {{7, 10}, {15, 22}};

  (A * B).Print("A * B");
  expected.Print("Expected");

  REQUIRE(expected == (A * B));
}

TEST_CASE("Rectangle matrix multiplication is correct", "[Matrix]") {
  Matrix A = {{1, 2}};
  A.Print();

  Matrix B = {{1}, {2}};
  B.Print();

  Matrix expected1 = {{5}};
  REQUIRE(expected1 == (A * B));

  Matrix expected2 = {{1, 2}, {2, 4}};

  (B * A).Print();
  REQUIRE(expected2 == (B * A));
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

  A.Transpose().Print("");

  REQUIRE(expected == (A.Transpose()));
}
