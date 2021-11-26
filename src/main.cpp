//
// Created by mateusz on 11/22/2021.
//
#define PLOT

#include "../include/Network.h"
#include <chrono>
#include <numeric>

#ifdef PLOT
#include <sciplot/sciplot.hpp>
#endif

double random(double start, double stop) {
  double x = (double) rand() / (double) RAND_MAX;
  x /= (stop - start);
  x += start;
  return x;
}

int main() {
  Network net(1, 4, 1);

  auto input = Eigen::MatrixXd(1, 1);
  input.fill(1);

  auto target = Eigen::MatrixXd(1, 1);
  target.fill(2);

  auto f = [](double x) {
    return 2 * x + 14;
  };

  std::vector<double> xs, abs_err;
  std::vector<uint64_t> timings;
  Eigen::MatrixXd out, err;
  int iterations = 100'000;
  timings.reserve(iterations);
  xs.reserve(iterations);
  abs_err.reserve(iterations);

  for (int i = 0; i < iterations; i++) {
    double x = random(0, 1);
    input.fill(x);
    target.fill(f(x));

    auto start = std::chrono::high_resolution_clock::now();
    out = net.FeedForward(input);
    err = net.Backpropagate(target);
    auto stop = std::chrono::high_resolution_clock::now();

    abs_err.push_back(std::abs(err.sum()));
    xs.push_back(i);
    timings.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
  }

  std::clog << "=== RESULTS ===" << std::endl
            << "In:" << std::endl
            << input << std::endl
            << "Target:" << std::endl
            << target << std::endl
            << "Out:" << std::endl
            << out << std::endl
            << "Err:" << std::endl
            << err << std::endl
            << std::endl;

  std::clog << std::endl
            << "Avg time (us): " << std::accumulate(timings.begin(), timings.end(), 0.0) / timings.size();

#ifdef PLOT
  sciplot::Plot plot;
  plot.xlabel("Iteration");
  plot.ylabel("Err");
//  plot.palette("dark2");
  plot.ytics().logscale();
  plot.drawCurve(xs, abs_err).lineColor("blue").label("Error");
  plot.show();
  plot.clear();
  plot.drawCurve(xs, timings).lineColor("red").label("Timings");
  plot.show();
#endif
}