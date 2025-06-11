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

  double step_with_gradient_norm_check()
  {
      double gradient_norm = 0;
      double adjoint_value = 0;
      size_t num_adjoints = 0;
      for (auto x : params)
      {
          adjoint_value = std::abs(x->adjoint());
          num_adjoints += 1;
          gradient_norm += adjoint_value*adjoint_value;
          *x -= lr * x->adjoint();
      }
      return (1.0/num_adjoints)*std::sqrt(gradient_norm);
  }


};
}  // namespace optimizers
#endif  // GRADIENTDESCENTOPTIMIZER_HPP
