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

  fs::path outFilePath = "";
  bool saveIntermediateResults = false;

  double LEARNING_RATE = 1e-2;
  size_t MAXITER = 1000000;
  double CONVERENCE_TOLERANCE = 1e-6;
  std::vector<double> initial_guess;
  bool is_initial_guess_provided() { return (initial_guess.size() > 0); }

  // optimizers::GenericGradientbasedOptimizer optimizer;
  std::string optimizer = "gds";

  std::string loss_function = "l2";
  void (*loss_fn)(aad::aVector*, Eigen::VectorX<double>*,
                  aad::ascalar*) = nullptr;
};

}  // namespace models
}  // namespace mznn
#endif  // MODELCONFIG_HPP
