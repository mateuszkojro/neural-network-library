//
// Created by mateusz on 11/22/2021.
//
#include <Network.h>

Network::Network(size_t input_size,
                 size_t hidden_size,
                 size_t output_size,
                 bool bias,
                 bool randomize,
                 std::function<double(double)> activation_function,
                 std::function<double(double)> activation_function_derivative) {

  activation_function_ = std::move(activation_function);
  activation_function_derivative_ = std::move(activation_function_derivative);

  hidden_ = Eigen::MatrixXd(hidden_size, 1u);
  input_ = Eigen::MatrixXd(input_size, 1u);
  input_bias_ = Eigen::MatrixXd(input_size, 1u);
  hidden_bias_ = Eigen::MatrixXd(hidden_size, 1u);
  output_bias_ = Eigen::MatrixXd(output_size, 1u);
  input_hidden_weights_ = Eigen::MatrixXd(hidden_size, input_size);
  hidden_output_weights_ = Eigen::MatrixXd(output_size, hidden_size);
  output_errors_ = Eigen::MatrixXd(output_size, 1u);

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

Eigen::MatrixXd Network::HadamardProduct(const Eigen::MatrixXd &a, const Eigen::MatrixXd &b) {
  return a.cwiseProduct(b);
}

const Eigen::MatrixXd &Network::FeedForward(const Eigen::MatrixXd &input) {

  output_ = input + input_bias_;
  input_ = output_;
  output_.unaryExpr(activation_function_);
  activation_input_ = output_;

  output_ = input_hidden_weights_ * output_;
  output_ += hidden_bias_;
  hidden_ = output_;
  output_.unaryExpr(activation_function_);
  activation_hidden_ = output_;

  output_ = hidden_output_weights_ * output_;
  output_ += output_bias_;
  activation_output_ = output_;
  activation_output_.unaryExpr(activation_function_);

  return activation_output_;
}

const Eigen::MatrixXd &Network::Backpropagate(const Eigen::MatrixXd &targets, double learning_rate) {
  auto f_prime = [this](Eigen::MatrixXd in) {
    in.unaryExpr(activation_function_derivative_);
    return in;
  };

  output_errors_ = f_prime(activation_output_ - targets);// * f_prime(output_);
  const auto &nabla_b_ho = output_errors_;
  auto nabla_w_ho = output_errors_ * hidden_.transpose();

  auto hidden_error = f_prime(hidden_output_weights_.transpose() * output_errors_);// * f_prime(hidden_);
  const auto &nabla_b_ih = hidden_error;
  auto nabla_w_ih = hidden_error * input_.transpose();

  hidden_output_weights_ -= nabla_w_ho * learning_rate;
  output_bias_ -= nabla_b_ho * learning_rate;

  input_hidden_weights_ -= nabla_w_ih * learning_rate;
  hidden_bias_ -= nabla_b_ih * learning_rate;

  return output_errors_;
}
const Eigen::MatrixXd &Network::Error() {
  return output_errors_;
}
