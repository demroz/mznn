#include <GradientDescentOptimizer.hpp>
#include <LinearRegression.hpp>
#include <limits>
#include <log.hpp>

#include "ModelUtilityFunctions.hpp"
namespace mznn {
namespace models {

LinearRegression::LinearRegression(const std::vector<std::vector<double>>& x,
                                   const std::vector<double>& y,
                                   ModelConfig config) {
  _config = config;
  _setup(x, y);
  if (_config.saveIntermediateResults) {
    _loss_vector.reserve(_config.MAXITER / 4);
  }
}

void LinearRegression::_setup(const std::vector<std::vector<double>>& x,
                              const std::vector<double>& y) {
  // x -> independent vars
  // y -> dependent vars
  // Linear system
  _initialize_linear_system(x, y);

  // initial guess calculations
  _x_initial_guess();

  /* initialize loss function */
  _initialize_loss();

  /* optimizer */
  _initialize_optimizer();
}

void LinearRegression::_initialize_linear_system(
    const std::vector<std::vector<double>>& x, const std::vector<double>& y) {
  const size_t numrows = x[0].size();
  const size_t datacols = x.size();
  const size_t numcols = datacols + 1;
  /* construct A and b in Ax = B */
  _A.resize(numrows, numcols);
  _b.resize(numrows);
  _A.col(0).setOnes();  // intercept

  _b = Eigen::Map<const Eigen::VectorXd>(y.data(), y.size());
  for (size_t j = 0; j < datacols; ++j) {
    Eigen::Map<const Eigen::VectorXd> columnMap(x[j].data(), numrows);
    _A.col(j + 1) = columnMap;
  }
  LOG_INFO("initialized linear system with {} unique points", _b.size());
}

void LinearRegression::_x_initial_guess() {
  /* set initial guess */
  _x.resize(_A.cols());
  if (_config.is_initial_guess_provided()) {
    LOG_INFO("initial guess provided");
    for (size_t col = 0; col < _A.cols(); ++col) {
      _x[col] = _config.initial_guess[col];
    }
  } else {
    LOG_INFO("initial guess not provided, set to zero");
    _x.setZero();  // seems to work after implementing correct copy constructor
    // for (size_t col = 0; col < _A.cols(); ++col) {
    //   _x[col] = 0.0;
    // }
  }
  /* construct array of references to trainable parameters to pass
   * to optimizer */
  for (size_t i = 0; i < _x.size(); ++i) {
    _coeffs.push_back(&_x[i]);
  }
  LOG_INFO("initialized system with {} trainable parameters", _x.size());
}

void LinearRegression::_initialize_loss() {
  if (!_config.loss_fn) {
    if (_config.loss_function == "l2") {
      LOG_INFO("loss function set to l2 loss");
      _config.loss_fn = &l2_loss;
    } else if (_config.loss_function == "l1") {
      LOG_INFO("loss funciton set to l1 loss");
      _config.loss_fn = &l1_loss;
    } else {
      LOG_CRITICAL("loss functional not implemented, will crash");
      throw NotImplemented(
          "loss funciton not implemented. only l1 and l2 loss is available for "
          "linear regression models");
    }
  }
}

void LinearRegression::_initialize_optimizer() {
  LOG_INFO(
      "optimizer set to regular gradient descent. Other optimizers not "
      "currently implemented");
  _optimizer = std::make_unique<optimizers::GradientDescent>(
      _coeffs, _config.LEARNING_RATE);
}

void LinearRegression::fit() {
  aad::ascalar::tape->mark();

  aad::ascalar loss;
  aad::aVector Ax(_b.size());

  size_t current_iteration = 0;

  double gradient_norm = std::numeric_limits<double>::infinity();

  while ((current_iteration < _config.MAXITER) &&
         (gradient_norm > _config.CONVERENCE_TOLERANCE)) {
    aad::ascalar::tape->rewindToMark();
    _optimizer->zero_grad();
    call(_A, Ax);
    _config.loss_fn(&Ax, &_b, &loss);
    loss.propagateToStart();
    gradient_norm = _optimizer->step_with_gradient_norm_check();
    ++current_iteration;
    if (_config.saveIntermediateResults) {
      _loss_vector.push_back(loss.item());
    }
    LOG_INFO("iteration: {}, loss: {}, gradient norm: {}", current_iteration,
             loss.item(), gradient_norm);
  }
  _final_loss = loss.item();
  _num_iterations_completed = current_iteration;
  _converged = (current_iteration < _config.MAXITER &&
                gradient_norm < _config.CONVERENCE_TOLERANCE);
  stats();
  print_summary();
}

void LinearRegression::stats() {
  /* variable setup, get everything
   * to be a double */
  aad::aVector y_pred_aad;
  y_pred_aad.resize(_b.size());
  call(_A, y_pred_aad);
  Eigen::VectorXd y_pred;
  y_pred.resize(_b.size());
  y_pred = y_pred_aad.unaryExpr(
      [](const aad::Scalar<double>& s) { return static_cast<double>(s); });

  /* r square and r square adjusted  */
  _compute_rsq(_b, y_pred);

  /* compute covariance */
  // estimate_parameter_covariance();
}

void LinearRegression::_compute_rsq(Eigen::Ref<Eigen::VectorXd> y_true,
                                    Eigen::Ref<Eigen::VectorXd> y_pred) {
  const double y_mean = y_true.mean();
  const double ss_tot = (y_true.array() - y_mean).square().sum();  // SST
  const double ss_res = (y_true - y_pred).array().square().sum();  // SSE
  const double ss_reg = ss_tot - ss_res;                           // SSR

  /* r square calculation */
  if (std::abs(ss_tot) < 1e-10) {
    _rsq = 0.0;
  } else {
    _rsq = 1.0 - (ss_res / ss_tot);
  }

  size_t n = y_true.size();
  size_t k = _A.cols() - 1;
  const double mse = ss_res / (n - k - 1);

  /* adjusted r square */
  _rsq_adj = 1.0 - (1.0 - _rsq) * ((n - 1.0) / (n - k - 1.0));

  /* covariance matrix and t test */
  _covariance_matrix = (_A.transpose() * _A).inverse();
  Eigen::JacobiSVD<Eigen::MatrixXd, Eigen::ComputeThinU | Eigen::ComputeThinV>
      svd(_covariance_matrix);
  Eigen::VectorXd singular_values = svd.singularValues();
  /* covariance matrix condition number */
  _condition_number =
      singular_values[0] / singular_values[singular_values.size() - 1];
  /* std err calculation */
  for (size_t i = 0; i < _x.size(); ++i) {
    _parameter_std_err.push_back(std::sqrt(mse * _covariance_matrix(i, i)));
  }

  /* t statistic */
  const double confidence_interval = 0.95;
  int dof = n - k - 1;
  for (size_t i = 0; i < _x.size(); ++i) {
    _t_values.push_back(_x[i].item() / _parameter_std_err[i]);
    double p_t;
    boost::math::students_t_distribution<double> dist(static_cast<double>(dof));
    p_t = 2.0 * boost::math::cdf(dist, -std::abs(_t_values[i]));
    _t_statistics.push_back(p_t);

    double alpha = (1.0 - confidence_interval) / 2;

    double t_critical =
        boost::math::quantile(dist, 1.0 - alpha);  // For the upper tail value

    double margin_of_error = t_critical * _parameter_std_err[i];

    _estimate_lower_bound.push_back(_x[i] - margin_of_error);
    _estimate_upper_bound.push_back(_x[i] + margin_of_error);
  }

  double df1 = static_cast<double>(k);
  double df2 = static_cast<double>(n - k - 1);

  if (df1 == 0.0 || df2 == 0.0) {
    _f_statistic = 0.0;
    _f_p_value = 1.0;
  } else {
    const double ms_reg = ss_reg / df1;
    const double ms_res = ss_res / df2;

    if (std::abs(ms_res) < 1e-10) {
      _f_statistic = std::numeric_limits<double>::infinity();
      _f_p_value = 0.0;
    } else {
      _f_statistic = ms_reg / ms_res;
      boost::math::fisher_f dist(df1, df2);
      _f_p_value = boost::math::cdf(dist, _f_statistic);
    }
  }
}

void LinearRegression::print_summary() {
  PrettyTable table;
  std::cout << "Autodiff based linear regression results\n";
  table.set_column_names({"", "", "", ""});
  table.add_row("loss type:  ", _config.loss_function,
                "optimizer:  ", _config.optimizer);
  table.add_row("learning rate:  ", _config.LEARNING_RATE, "maximum iterations",
                _config.MAXITER);
  table.add_row("final loss:  ", _final_loss,
                "number of iterations:  ", _num_iterations_completed);
  table.add_row("converged:  ", _converged ? "yes" : "no", "", "");

  table.add_row("R-squared:", _rsq, "Adj. R-squared:", _rsq_adj);
  table.add_row("F-statistic", _f_statistic, "Prob. (F-statistic)", _f_p_value);
  table.print();
  PrettyTable fit_value_table;
  fit_value_table.set_column_names(std::vector<std::string>{
      "  variable  ", "  value  ", "  std err  ", "   t   ", "   P>|t|   ",
      "   [0.025   ", "   0.975]   "});
  fit_value_table.add_row("intercept", _x[0].item(), _parameter_std_err[0],
                          _t_values[0], _t_statistics[0],
                          _estimate_lower_bound[0], _estimate_lower_bound[0]);
  for (size_t i = 1; i < _x.rows(); ++i) {
    fit_value_table.add_row(std::format("beta_{}", i), _x[i].item(),
                            _parameter_std_err[i], _t_values[i],
                            _t_statistics[i], _estimate_lower_bound[i],
                            _estimate_upper_bound[i]);
  }
  table.print();
  fit_value_table.print();
}

void LinearRegression::_record_intermediate_regression_state(double& loss) {
  _loss_vector.push_back(loss);
  std::vector<double> regression_coefficients;
  for (auto x : _x) {
    regression_coefficients.push_back(x.item());
  }
  _internal_regression_state.push_back(regression_coefficients);
}

void LinearRegression::call(const Eigen::MatrixX<double>& lhs,
                            Eigen::Ref<aad::aVector> rhs) {
  rhs = lhs * _x;
}

std::vector<double> LinearRegression::call(
    const std::vector<std::vector<double>>& xvars) {
  std::vector<double> pred(xvars[0].size(), 0.0);
  for (size_t j = 0; j < xvars.size(); ++j) {
    for (size_t i = 0; i < xvars[0].size(); ++i) {
      pred[i] += _x(i).item() * xvars[j][i];
    }
  }
  return pred;
}
void LinearRegression::call_loss(aad::aVector* x, Eigen::VectorX<double>* y,
                                 aad::ascalar* loss) {
  return _config.loss_fn(x, y, loss);
}

}  // namespace models
}  // namespace mznn
