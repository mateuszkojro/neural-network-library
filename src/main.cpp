//
// Created by mateusz on 11/22/2021.
//

#include "../include/Network.h"
#include <chrono>
#include <fstream>
#include <numeric>

#ifdef MK_WITH_PLOT
#include <sciplot/sciplot.hpp>
#endif

double random(double start, double stop) {
  double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
  x /= (stop - start);
  x += start;
  return x;
}

struct LabelAndInput {
  Eigen::MatrixXd label;
  Eigen::MatrixXd input;
};

Eigen::MatrixXd ReadFile(std::fstream &fd) {

  std::string broken_class_name;
  int size_x, size_y;
  fd >> broken_class_name;
  fd >> size_x;
  fd >> size_y;

  Eigen::MatrixXd image(size_x, size_y);
  for (size_t y = 0; y < size_y; y++) {
    for (size_t x = 0; x < size_x; x++) {
      char value;
      fd >> value;
      image(x, y) = value - '0';
    }
  }
  return image;
}

class Dataset {
 public:
  Dataset(const std::string &path, size_t number_of_elements) {

    Eigen::MatrixXd label_c(2, 1);
    label_c(1) = 0;
    label_c(0) = 1;

    Eigen::MatrixXd label_o(2, 1);
    label_o(1) = 1;
    label_o(0) = 0;

    for (int i = 0; i < number_of_elements; i++) {
      std::fstream fdo, fdc;
      auto name_o = path + "\\o" + std::to_string(i % 6) + ".txt";
      auto name_c = path + "\\c" + std::to_string(i % 6) + ".txt";

      fdo.open(name_o);
      fdc.open(name_c);

      if (fdc.bad() || fdo.bad())
        assert(false && "file was bad");

      dataset_.push_back(Distort({label_o, ReadFile(fdo)}, 0.01));
      dataset_.push_back(Distort({label_c, ReadFile(fdc)}, 0.01));

      fdo.close();
      fdc.close();
    }
  }
  const LabelAndInput &GetTrainingIteration(size_t i) {
    return dataset_.at(i);
  }

  const LabelAndInput &GetTestingIteration(size_t i) {
    return dataset_.at(i);
  }

  size_t Size() { return dataset_.size(); }

  static LabelAndInput Distort(const LabelAndInput &data, double distortion_probabilty) {
    //    return data;
    auto copy = data;
    for (size_t i = 0; i < copy.input.size(); i++) {
      if (random(0, 1) <= distortion_probabilty) {
        copy.input(i) = static_cast<Eigen::DenseCoeffsBase<class Eigen::Matrix<double, -1, -1, 0>, 1>::Scalar>(!static_cast<bool>(copy.input(i)));
      }
    }
    return copy;
  }

 private:
  std::vector<LabelAndInput> dataset_;
};

int images() {
  Dataset d(R"(C:\w\neural-network-library\dataset)", 10000);
  Network net(100, 10, 2);
  std::vector<double> abs_err;
  abs_err.reserve(d.Size());
  std::vector<double> xs;
  std::vector<double> predictions;
  std::vector<double> labels;

  for (int i = 0; i < d.Size(); i++) {
    const auto &[label_raw, input_raw] = d.GetTrainingIteration(i);
    auto input = input_raw.reshaped(100, 1);
    auto label = label_raw.reshaped(2, 1);

    auto out = net.FeedForward(input);
    auto err = net.Backpropagate(label, 0.01);

    abs_err.push_back(std::abs(err.sum()));
    predictions.push_back(out(0));
    labels.push_back(label(0));
    xs.push_back(i);

//    std::cout << "Iter: " << i << " Err: " << abs_err.back() << std::endl;
//    std::cout << "Pred: " << out << " Label: " << label << std::endl;
//    if (i == 20) {
//      break;
//    }
  }

#ifdef MK_WITH_PLOT
  sciplot::Plot plot;
  plot.xlabel("Iteration");
  plot.ylabel("Err");
  //  plot.ytics().logscale();
  plot.drawCurve(xs, abs_err).lineColor("blue").label("Error");
  plot.show();
  plot.clear();
  plot.xlabel("Iteration");
  //  plot.ylabel("Err");
  //  plot.ytics().logscale();
  plot.drawCurve(xs, labels).lineColor("blue").label("Label");
  plot.drawCurve(xs, predictions).lineColor("red").label("Prediction");
  plot.show();
#endif
  return 0;
}

int linear_function() {
  Network net(1, 4, 1);

  auto input = Eigen::MatrixXd(1, 1);
  input.fill(1);

  auto target = Eigen::MatrixXd(1, 1);
  target.fill(2);

  auto f = [](double x) {
    return 2 * x;
  };

  std::vector<double> xs;
  std::vector<double> abs_err;

  std::vector<uint64_t> timings;

  Eigen::MatrixXd out;
  Eigen::MatrixXd err;

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

#ifdef MK_WITH_PLOT
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
  return 0;
}

int main() {
  images();
  //  linear_function();
}