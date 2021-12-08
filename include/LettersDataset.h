//
// Created by M.Kojro on 12/8/2021.
//

#ifndef NEURAL_NETWORK_C__INCLUDE_LETTERSDATASET_H_
#define NEURAL_NETWORK_C__INCLUDE_LETTERSDATASET_H_

#include <Eigen/Core>
#include <fstream>
#include <vector>

double random(double start, double stop) {
  double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
  x /= (stop - start);
  x += start;
  return x;
}

struct LabelAndInput
{
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
  Dataset(const std::string &path, size_t number_of_elements, double distortion_rate = 0.01) {

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

      if (fdc.bad() || fdo.bad()) assert(false && "file was bad");

      dataset_.push_back(Distort({label_o, ReadFile(fdo)}, distortion_rate));
      dataset_.push_back(Distort({label_c, ReadFile(fdc)}, distortion_rate));

      fdo.close();
      fdc.close();
    }
  }
  const LabelAndInput &GetTrainingIteration(size_t i) { return dataset_.at(i); }

  const LabelAndInput &GetTestingIteration(size_t i) { return dataset_.at(i); }

  size_t Size() { return dataset_.size(); }

  static LabelAndInput Distort(const LabelAndInput &data,
                               double distortion_probabilty) {
    //    return data;
    auto copy = data;
    for (size_t i = 0; i < copy.input.size(); i++) {
      if (random(0, 1) <= distortion_probabilty) {
        copy.input(i) = abs(1 - copy.input(i));
      }
    }
    return copy;
  }

 private:
  std::vector<LabelAndInput> dataset_;
};
#endif  // NEURAL_NETWORK_C__INCLUDE_LETTERSDATASET_H_
