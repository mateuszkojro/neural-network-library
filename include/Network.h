//
// Created by mateusz on 11/22/2021.
//

#ifndef NEURAL_NETWORK_C__INCLUDE_NETWORK_H_
#define NEURAL_NETWORK_C__INCLUDE_NETWORK_H_
#include <functional>
#include <iostream>
#include <utility>

#include <Eigen/Core>

static double logistic(double x) {
  return 1.0 / (1.0 + std::exp(-x));
}

static double logistic_derivative(double x) {
  return logistic(x) * (1.0 - logistic(x));
}

static Eigen::MatrixXd BinaryCrossEntropySingleError(Eigen::MatrixXd predicted, Eigen::MatrixXd expected) {
  assert(predicted.size() == 1 && expected.size() == 1 && "Binary cross entropy requires one value for the result and prediction");
  Eigen::MatrixXd res(1, 1);
  res(0) = -(expected(0) * std::log(predicted(0))
             + (1.0 - expected(0)) * std::log(1.0 - predicted(0)));
  return res;
}

static Eigen::MatrixXd BinaryCrossEntropyError(Eigen::MatrixXd predicted, Eigen::MatrixXd expected) {
  Eigen::MatrixXd res(1, 1);

  for (int i = 0; i < predicted.size(); i++) {
    res(0) += -(expected(i) * std::log(predicted(i))
               + (1.0 - expected(i)) * std::log(1.0 - predicted(i)));
  }
  return res;
}
#ifdef LOG_LOSS

static double softmax(double x, double sum) {
  return std::exp(x) / std::exp(sum);
}

#endif

class NetworkLayer {
 private:
  size_t input_nodes_;
  size_t output_nodes_;
};

class Network {
 public:
  Network(size_t input_size,
          size_t hidden_size,
          size_t output_size,
          bool bias = true,
          bool randomize = true,
          std::function<double(double)> activation_function = logistic,
          std::function<double(double)> activation_function_derivative = logistic_derivative);

  const Eigen::MatrixXd &FeedForward(const Eigen::MatrixXd &input);
  const Eigen::MatrixXd &Backpropagate(const Eigen::MatrixXd &targets, double learning_rate = 0.1);

  const Eigen::MatrixXd &Error();

 private:
  Eigen::MatrixXd HadamardProduct(const Eigen::MatrixXd &a, const Eigen::MatrixXd &b);

  Eigen::MatrixXd input_bias_;
  Eigen::MatrixXd hidden_bias_;
  Eigen::MatrixXd output_bias_;

  Eigen::MatrixXd input_hidden_weights_;
  Eigen::MatrixXd hidden_output_weights_;

  Eigen::MatrixXd output_;
  Eigen::MatrixXd hidden_;
  Eigen::MatrixXd input_;

  Eigen::MatrixXd activation_output_;
  Eigen::MatrixXd activation_hidden_;
  Eigen::MatrixXd activation_input_;

  Eigen::MatrixXd output_errors_;

  std::function<double(double)> activation_function_;
  std::function<double(double)> activation_function_derivative_;
};

#endif//NEURAL_NETWORK_C__INCLUDE_NETWORK_H_
