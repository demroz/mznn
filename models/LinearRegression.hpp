#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include <rapidcsv.h>

#include <Eigen/Eigen>
#include <Eigen/SVD>
#include <GradientDescentOptimizer.hpp>
#include <ModelConfig.hpp>
#include <PrettyTable.hpp>
#include <addutils.hpp>
#include <autodiff.hpp>
#include <boost/math/distributions/fisher_f.hpp>
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <filesystem>
#include <format>
#include <log.hpp>
#include <string>
#include <vector>
namespace mznn {
namespace models {
namespace fs = std::filesystem;

class LinearRegression {
 private:
  /* dataset to fit
   * expected format
   *
   * x_i -> independet variables
   * y -> dependent variable
   *
   * x_0varname, x_1varname, ... , yvarname
   * data_x0, data_x1, ..., data_y
   */
  /* friend class for testing */
  friend class LinearRegressionTest;
  // std::vector<double>
  //    _lossVector;  // vector of loss values to plot loss function if needed
  ModelConfig _config;

  std::vector<aad::ascalar*>
      _coeffs;  // linear regression coefficients pointers to values

  Eigen::MatrixX<double> _A;  // internal matrix
  Eigen::MatrixX<double> _covariance_matrix;
  Eigen::VectorX<double> _b;  // intenral vector
  aad::aVector _x;            // linear regression coefficients, data

  double _rsq;
  double _rsq_adj;
  double _condition_number;
  std::vector<double> _parameter_std_err;
  std::vector<double> _estimate_lower_bound;
  std::vector<double> _estimate_upper_bound;
  double _f_statistic;
  double _f_p_value;

  std::vector<double> _t_values;
  std::vector<double> _t_statistics;
  std::vector<double> _loss_vector;
  std::vector<std::vector<double>> _internal_regression_state;

  double _final_loss;
  size_t _num_iterations_completed;
  bool _converged;

  void _record_intermediate_regression_state(double& loss);
  void _setup(const std::vector<std::vector<double>>& x,
              const std::vector<double>& y);
  void _initialize_linear_system(const std::vector<std::vector<double>>& x,
                                 const std::vector<double>& y);
  void _x_initial_guess();
  void _initialize_loss();
  void _initialize_optimizer();
  void _iteration();

  void _compute_rsq(Eigen::Ref<Eigen::VectorXd> y_true,
                    Eigen::Ref<Eigen::VectorXd> y_pred);

  /* enables choice for loss functions */
  void (LinearRegression::* _loss_fn())(aad::aVector*, Eigen::VectorX<double>*,
                                        aad::ascalar*);
  std::unique_ptr<optimizers::GenericGradientbasedOptimizer> _optimizer;

 public:
  LinearRegression(
      const std::vector<std::vector<double>>& x, /* independent variables */
      const std::vector<double>& y,              /* dependent variables   */
      ModelConfig config /* model config for optional args */
  );

  ModelConfig get_model_config() { return _config; }
  void fit();
  void stats();
  // void estimate_parameter_covariance();
  void print_summary();
  void call(const Eigen::MatrixX<double>& lhs, Eigen::Ref<aad::aVector> rhs);
  // void call(const std::vector<double>& lhs, std::vector<double>& rhs);
  // aad::aVector call(const Eigen::MatrixX<double>& lhs);
  std::vector<double> call(const std::vector<std::vector<double>>& xvars);

  void call_loss(aad::aVector* x, Eigen::VectorX<double>* y,
                 aad::ascalar* loss);
};
};  // namespace models
};  // namespace mznn
#endif  // LINEARREGRESSION_HPP
