#include "Net.h"
#include "Matrix.h"

/// Create NN
/// \param input Number of input nodes
/// \param hidden Number of hidden nodes
/// \param output Number of output nodes
/// \param learning_rate Learning rate
/// \param activation_func Activation function
/// \param derivative Derivative of activation function
Net::Net(int input, int hidden, int output, double learning_rate,
         double (*activation_func)(double), double (*derivative)(double))
    : learning_rate_(learning_rate), activation_func_(activation_func),
      derivative_(derivative) {

  // -------------------------
  // ------ Rows X Cols ------
  // -------------------------

  input_ = Matrix::ColVector(input);
  hidden_ = Matrix::ColVector(hidden);
  output_ = Matrix::ColVector(output);

  weights_input_h_ = Matrix::RowsXCols(hidden, input);
  weights_hidden_o_ = Matrix::RowsXCols(output, hidden);
  weights_input_h_.RandomFill();
  weights_hidden_o_.RandomFill();

  bias_hidden_ = Matrix::RowVector(hidden);
  bias_output_ = Matrix::RowVector(output);
  bias_hidden_.RandomFill();
  bias_output_.RandomFill();
}

/// Make one feed-forward pass on defined Neural Network
/// \param a Input for NN
/// \return  Output of Feed forward
Matrix Net::Predict(const Matrix &a) const {

  throw "Not that";

  const Matrix &input = a;

  Matrix hidden = input * weights_input_h_;
  hidden = hidden + bias_hidden_;
  hidden = hidden.ApplyFunction(activation_func_);

  Matrix output = hidden * weights_hidden_o_;
  output = output + bias_output_;
  output = output.ApplyFunction(activation_func_);

  return output;
}

/// Make one pass over whole NN (feed forward and backpropagation)
/// \param input Input data
/// \param labels Expected output for input data
void Net::Teach(const Matrix &input, const Matrix &labels) {

  //   calculate values with current weights
  //  Matrix prediction = Predict(input);

  throw "Not implemented";

  Matrix hidden = input * weights_input_h_;
  hidden = hidden + bias_hidden_;
  hidden = hidden.ApplyFunction(activation_func_);

  Matrix output = hidden * weights_hidden_o_;
  output = output + bias_output_;
  output = output.ApplyFunction(activation_func_);

  Matrix output_errors = labels - output_;
  // calculate gradient
  Matrix gradient = output_;
  gradient.ApplyFunction(derivative_);

  gradient = gradient * output_errors.Transpose();
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

Matrix Net::FeedForward(const Matrix &A) const {

// Orginaly:  Matrix hidden = weights_input_h_ * A;
  hidden_.Print("Hidden");
  weights_input_h_.Print("weights_input_h");
  A.Print("A");

  Matrix hidden = weights_input_h_ * A;
  hidden = hidden + bias_hidden_;
  hidden.ApplyFunction(activation_func_);

  Vector output = weights_hidden_o_ * hidden;
  output = output + bias_output_;
  output.ApplyFunction(activation_func_);

  return output;
}

void Net::BacPropagate(const Matrix &input, const Matrix &labels) {

  input_ = input;

  Matrix prediction = FeedForward(input);

  Matrix output_errors = labels - prediction;

  Matrix gradients = output_errors.ApplyFunction(derivative_);
  gradients = gradients * output_errors;
  gradients = gradients * learning_rate_;

  Matrix hidden_T = hidden_.Transpose();

  // Let's calculate how much to change weight hidden-out
  Matrix weights_hod = gradients * hidden_T;
  weights_hidden_o_ = weights_hidden_o_ + weights_hod;

  bias_output_ = bias_output_ + gradients;

  Matrix weights_ho_T = weights_hidden_o_.Transpose();
  Matrix hidden_errors = weights_ho_T * output_errors;

  Matrix hidden_gradient = hidden_.ApplyFunction(derivative_);
  hidden_gradient = hidden_gradient * hidden_errors;
  hidden_gradient = hidden_gradient * learning_rate_;

  Matrix inputs_T = input.Transpose();
  Matrix weights_ihd = hidden_gradient * inputs_T;

  weights_input_h_ = weights_input_h_ + weights_ihd;
  bias_hidden_ = hidden_gradient;
}
