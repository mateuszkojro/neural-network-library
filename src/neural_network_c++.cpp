#include "Net.h"
#include <cmath>

int n = 0;

double act(double x) { return tanh(x); }

double act_d(double x) { return 1 - (x * x); }

int main() {

  double **tab1;
  double **tab2;

  int size = 3;

  // przygotowanie tablic testowych

  tab1 = new double *[size];
  tab2 = new double *[size];

  for (int i = 0; i < size; i++) {
    tab1[i] = new double[1];
    tab2[i] = new double[1];
  }

  tab1[0][0] = 1;
  tab1[1][0] = 4;
  tab1[2][0] = 7;

  tab2[0][0] = 2;
  tab2[1][0] = 1;
  tab2[2][0] = 3;

  /*

  tab1[0][0] = 1; tab1[0][1] = 2; tab1[0][2] = 3;
  tab1[1][0] = 1; tab1[1][1] = 2; tab1[1][2] = 3;
  tab1[2][0] = 1; tab1[2][1] = 2; tab1[2][2] = 3;

  tab2[0][0] = 1; tab2[0][1] = 1; tab2[0][2] = 1;
  tab2[1][0] = 2; tab2[1][1] = 1; tab2[1][2] = 2;
  tab2[2][0] = 3; tab2[2][1] = 2; tab2[2][2] = 1;

  */

  auto test_f = [](double x) { return x++; };

  // (rozmiar_w_x,rozmiar_w_y)
  matrix x1(size, 1), x2(size, 1), x3(size, 1);

  x1.fill_table(tab1);
  x2.fill_table(tab2);

  Net test(3, 5, 3, 0.1, act, act_d);

  x1.show();

  test.Predict(x1);

  test.output_.show();
  test.Teach(x1, x2);
  test.output_.show();
}

// WARRNINGS
//- nie czyszcze danych z heap