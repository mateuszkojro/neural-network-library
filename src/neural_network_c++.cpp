#include "Net.h"
#include <cmath>

int n = 0;

double act(double x) { return tanh(x); }

double act_d(double x) { return 1 - (x * x); }

int main() {

  Matrix x_1 = {{1}, {1}, {1}};
  Matrix x_2 = {{2}, {2}, {2}};

  Net test(3, 5, 3, 0.1, act, act_d);

  x_1.Print();

  auto prediction = test.Predict(x_1);

  test.output_.Print();
  test.Teach(x_1, x_2);
  test.output_.Print();
}

// WARRNINGS
//- nie czyszcze danych z heap