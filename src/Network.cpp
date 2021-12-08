//
// Created by M.Kojro on 11/22/2021.
//

#include <Network.h>

Network::Network(size_t input_size, size_t hidden_size, size_t output_size,
                 bool bias, bool randomize,
                 std::function<double(double)> activation_function,
                 std::function<double(double)> activation_function_derivative) {

  activation_function_ = std::move(activation_function);
  activation_function_derivative_ = std::move(activation_function_derivative);

  hidden_ = Eigen::MatrixXd(hidden_size, 1U);
  input_ = Eigen::MatrixXd(input_size, 1U);
  input_bias_ = Eigen::MatrixXd(input_size, 1U);
  hidden_bias_ = Eigen::MatrixXd(hidden_size, 1U);
  output_bias_ = Eigen::MatrixXd(output_size, 1U);
  input_hidden_weights_ = Eigen::MatrixXd(hidden_size, input_size);
  hidden_output_weights_ = Eigen::MatrixXd(output_size, hidden_size);
  output_errors_ = Eigen::MatrixXd(output_size, 1U);

  if (randomize) {
    hidden_.setRandom();
    input_.setRandom();
    input_hidden_weights_.setRandom();
    hidden_output_weights_.setRandom();
    output_errors_.setRandom();

  } else {
    assert(false && "Not random initialisation is not yet implemented");
  }
  if (bias) {
    input_bias_.setRandom();
    hidden_bias_.setRandom();
    output_bias_.setRandom();
  } else {
    // FIXME: That does not remove the bias completely
    input_bias_.fill(0);
    hidden_bias_.fill(0);
    output_bias_.fill(0);
  }
}

Eigen::MatrixXd Network::HadamardProduct(const Eigen::MatrixXd &a,
                                         const Eigen::MatrixXd &b) {
  return a.cwiseProduct(b);
}

const Eigen::MatrixXd &Network::FeedForward(const Eigen::MatrixXd &input) {

  output_ = input + input_bias_;
  input_ = output_;
  output_ = output_.unaryExpr(activation_function_);
  activation_input_ = output_;

  output_ = input_hidden_weights_ * output_;
  output_ += hidden_bias_;
  hidden_ = output_;
  output_ = output_.unaryExpr(activation_function_);
  activation_hidden_ = output_;

  output_ = hidden_output_weights_ * output_;
  output_ += output_bias_;
  activation_output_ = output_;
  activation_output_ = activation_output_.unaryExpr(activation_function_);

  return activation_output_;
}

static Eigen::MatrixXd SimpleError(const Eigen::MatrixXd &predicted,
                                   const Eigen::MatrixXd &target) {
  return target - predicted;
}

const Eigen::MatrixXd &Network::Backpropagate(const Eigen::MatrixXd &targets,
                                              double learning_rate) {

  output_errors_ = SimpleError(activation_output_, targets);

  Eigen::MatrixXd output_gradients =
      output_.unaryExpr(activation_function_derivative_);
  output_gradients = HadamardProduct(output_errors_, output_gradients);
  output_gradients *= learning_rate;

  auto who_deltas = output_gradients * hidden_.transpose();
  // Update last
  hidden_output_weights_ += who_deltas;

  output_bias_ += output_gradients;

  auto hidden_errors = hidden_output_weights_.transpose() * output_errors_;
  Eigen::MatrixXd hidden_gradient =
      hidden_.unaryExpr(activation_function_derivative_);
  hidden_gradient = HadamardProduct(hidden_gradient, hidden_errors);
  hidden_gradient *= learning_rate;

  auto weights_ih_deltas = hidden_gradient * input_.transpose();

  // Update first
  input_hidden_weights_ += weights_ih_deltas;
  hidden_bias_ += hidden_gradient;

  return output_errors_;
}

 const Eigen::MatrixXd &Network::Error() { return output_errors_; }
