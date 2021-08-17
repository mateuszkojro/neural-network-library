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

  auto prediction = test.FeedForward(x_1);

  prediction.Print("Prediction");

  test.output_.Print();
  test.BacPropagate(x_1, x_2);
  test.output_.Print();
}

// WARRNINGS
//- nie czyszcze danych z heap