#ifndef GENERICGRADIENTBASEDOPTIMIZER_HPP
#define GENERICGRADIENTBASEDOPTIMIZER_HPP
#include <autodiff.hpp>
namespace optimizers {
class GenericGradientbasedOptimizer {
 public:
  std::vector<aad::ascalar*> params;
  double lr = 1e-3;
  double momentum = 0.9;

  /* constructors */
  GenericGradientbasedOptimizer() {};
  GenericGradientbasedOptimizer(std::vector<aad::ascalar*>& parameters)
      : params(parameters) {};
  GenericGradientbasedOptimizer(std::vector<aad::ascalar*>& parameters,
                                double learning_rate)
      : params(parameters), lr(learning_rate) {};
  GenericGradientbasedOptimizer(std::vector<aad::ascalar*>& parameters,
                                double learning_rate, double momentum)
      : params(parameters), lr(learning_rate), momentum(momentum) {};

  virtual ~GenericGradientbasedOptimizer() = default;
  void zero_grad() { aad::ascalar::tape->resetAdjoints(); }
  virtual void step() {};
  virtual double step_with_gradient_norm_check() {return 0.0;};
};
}  // namespace optimizers
#endif  // GENERICGRADIENTBASEDOPTIMIZER_HPP
