#include "Net.h"
#include "Matrix.h"

Net::Net(int input, int hidden, int output, double learning_rate,
         double (*activation_func)(double), double (*derivative)(double))
    : learning_rate_(learning_rate), activation_func_(activation_func),
      derivative_(derivative) {

  input_ = Matrix(1, input);
  hidden_ = Matrix(1, hidden);
  output_ = Matrix(1, output);

  weights_input_h_ =
      Matrix(input, hidden);// kolejnosc jest wazna a nie wiem czy ta jest ok
  weights_hidden_o_ = Matrix(hidden, output);
  weights_input_h_.RandomFill();
  weights_hidden_o_.RandomFill();

  bias_hidden_ = Matrix(hidden, 1);
  bias_output_ = Matrix(output, 1);
  bias_hidden_.RandomFill();
  bias_output_.RandomFill();
}

Matrix Net::Predict(const Matrix &a) const {

  const Matrix& input = a;

  Matrix hidden = input * weights_input_h_;
  hidden = hidden + bias_hidden_;
  hidden.ApplyFunction(activation_func_);

  Matrix output = hidden * weights_hidden_o_;
  output = output + bias_output_;
  output.ApplyFunction(activation_func_);

  return output;
}

void Net::Teach(const Matrix &input, const Matrix &labels) {
  /*

  JESZCZE RAZ BO KOMPLETNIE NIE JESTEM PEWNY TEGO CZY TO JEST OK

  */

  //   calculate values with current weights
  //  Matrix prediction = Predict(input);

  Matrix hidden = weights_input_h_ * input;
  hidden = hidden + bias_hidden_;
  hidden.ApplyFunction(activation_func_);

  Matrix output = weights_hidden_o_ * hidden;
  output = output + bias_output_;
  output.ApplyFunction(activation_func_);

  Matrix output_errors = labels - output_;
  // calculate gradient
  Matrix gradient = output_;
  gradient.ApplyFunction(derivative_);

  gradient = gradient * output_errors;
  gradient = gradient * learning_rate_;

  // calculate delta
  Matrix hidden_t = hidden_.Transpose();
  Matrix weights_hidden_o_delta = gradient * hidden_t;

  weights_hidden_o_ = weights_hidden_o_ + weights_hidden_o_delta;
  bias_output_ = bias_output_ + gradient;

  Matrix who_t = weights_hidden_o_.Transpose();
  Matrix hidden_errors = who_t * output_errors;

  Matrix hidden_gradient = hidden_;
  hidden_gradient.ApplyFunction(derivative_);

  hidden_gradient = hidden_gradient * hidden_errors;
  hidden_gradient = hidden_gradient * learning_rate_;

  Matrix input_t = input.Transpose();
  Matrix weights_input_h_delta = hidden_gradient * input_t;
  weights_input_h_ = weights_input_h_ + weights_hidden_o_delta;
  bias_hidden_ = bias_hidden_ + hidden_gradient;
}
