#pragma once

#include "Matrix.h"
#include "matrix.h"

// moze przerobic wszystkie macierze na wskazniki

class Net {
private:
public:
  Net(int input, int hidden, int output, double learning_rate,
      double (*activation_func)(double), double (*derivative)(double ));
  Matrix input_;

  Matrix hidden_;

  Matrix output_;

  double learning_rate_;
  double (*activation_func_)(double);
  double (*derivative_)(double);

  Matrix weights_input_h_;
  Matrix weights_hidden_o_;

  Matrix bias_hidden_;
  Matrix bias_output_;


  void feed_forward();
  void bacpropagate();
  void calculate_error();

  void Predict(const Matrix& a);
  void Teach(const Matrix &input, const Matrix &train_data);


  void export_json();
  void export_binary();

  void load_json();
  void load_binary();
};
