#ifndef MODELCONFIG_HPP
#define MODELCONFIG_HPP

#include <rapidcsv.h>

#include <Eigen/Eigen>
#include <GradientDescentOptimizer.hpp>
#include <addutils.hpp>
#include <autodiff.hpp>
#include <filesystem>
#include <log.hpp>
#include <string>
#include <vector>
namespace mznn {
namespace models {
namespace fs = std::filesystem;

struct ModelConfig {
  ModelConfig() = default;
  fs::path inFilePath = "";
  fs::path outFilePath = "";
  bool saveIntermediateResults = false;

  std::vector<double> lossArray;

  double LEARNING_RATE = 1e-4;
  size_t MAXITER = 10000;
  double CONVERENCE_TOLERANCE = 1e-6;
};

}  // namespace models
}  // namespace mznn
#endif  // MODELCONFIG_HPP
