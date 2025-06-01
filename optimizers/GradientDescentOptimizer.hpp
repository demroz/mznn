#ifndef GRADIENTDESCENTOPTIMIZER_HPP
#define GRADIENTDESCENTOPTIMIZER_HPP
#include <autodiff.hpp>

#include "GenericGradientBasedOptimizer.hpp"

namespace optimizers {
class GradientDescent : public GenericGradientbasedOptimizer {
 private:
 public:
  GradientDescent(std::vector<aad::ascalar*>& variables, double learning_rate)
      : GenericGradientbasedOptimizer(variables, learning_rate) {};
  ~GradientDescent() = default;
  void step() {
    for (auto x : params) {
      *x -= lr * x->adjoint();
    }
  }
};
}  // namespace optimizers
#endif  // GRADIENTDESCENTOPTIMIZER_HPP
