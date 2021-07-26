#include "Net.h"
#include "Matrix.h"

Net::Net(int input, int hidden, int output, double learning_rate,
         double (*activation_func)(double))
    : learning_rate_(learning_rate), activation_func_(activation_func) {

  input_.init(1, input);
  hidden_.init(1, hidden);
  output_.init(1, output);

  weights_input_h_.init(
      hidden,
      input); // kolejnosc jest wazna a nie wiem czy ta jest ok
  weights_hidden_o_.init(output, hidden);
  weights_input_h_.RandomFill();
  weights_hidden_o_.RandomFill();

  bias_hidden_.init(hidden, 1);
  bias_output_.init(output, 1);
  bias_hidden_.RandomFill();
  bias_output_.RandomFill();
}

void Net::Predict(const Matrix &a) {

  input_ = a;

  hidden_ = weights_input_h_ * input_;
  hidden_ = hidden_ + bias_hidden_;
  hidden_.ApplyFunction(activation_func_);

  output_ = weights_hidden_o_ * hidden_;
  output_ = output_ + bias_output_;
  output_.ApplyFunction(activation_func_);
}

void Net::Teach(const Matrix &input, const Matrix &train_data) {
  /*

  JESZCZE RAZ BO KOMPLETNIE NIE JESTEM PEWNY TEGO CZY TO JEST OK

  */

  // calculate values with current weights
  Predict(input);

  Matrix output_errors = train_data - output_;
  // calculate gradient
  Matrix gradient = output_;
  gradient.ApplyFunction(d_func);
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
  hidden_gradient.ApplyFunction(d_func);
  hidden_gradient = hidden_gradient * hidden_errors;
  hidden_gradient = hidden_gradient * learning_rate_;

  Matrix input_t = input.Transpose();
  Matrix weights_input_h_delta = hidden_gradient * input_t;
  weights_input_h_ = weights_input_h_ + weights_hidden_o_delta;
  bias_hidden_ = bias_hidden_ + hidden_gradient;
}
