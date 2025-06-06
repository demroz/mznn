#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

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

class LinearRegression {
 private:
  fs::path _infilePath;
  fs::path _outfilePath;

  /* dataset to fit
   * expected format
   *
   * x_i -> independet variables
   * y -> dependent variable
   *
   * x_0varname, x_1varname, ... , yvarname
   * data_x0, data_x1, ..., data_y
   */

  std::vector<double>
      _lossVector;  // vector of loss values to plot loss function if needed
  std::vector<aad::ascalar*>
      _coeffs;  // linear regression coefficients pointers to values

  std::vector<std::string> _columnNames;  // column names of csv file
  size_t _numIndepVars;                   // the x's
  size_t _numrows;                        // number of data points
  bool _dumpToFile;
  bool _saveIntermediateresults;

  Eigen::MatrixX<double> _A;  // internal matrix
  Eigen::VectorX<double> _b;  // intenral vector
  aad::aVector _x;            // linear regression coefficients, data
  double _learning_rate = 1e-4;
  size_t _MAXITER = 10000;  // maximum iterations
  double _CONVERGENCE_TOLERANCE = 1e-6;

  void _loadFile(fs::path, std::vector<std::string>, std::string);

  void _initRandomLowHigh(double low, double high);
  void _initWithGuess(std::vector<double> guess);
  void _setup();

  void _l1loss(aad::aVector* x, Eigen::VectorX<double>* y, aad::ascalar* loss);
  void _l2loss(aad::aVector* x, Eigen::VectorX<double>* y, aad::ascalar* loss);

  /* enables choice for loss functions */
  void (LinearRegression::* _loss_fn())(aad::aVector*, Eigen::VectorX<double>*,
                                        aad::ascalar*);
  optimizers::GenericGradientbasedOptimizer _optimizer;

 public:
  LinearRegression(
      fs::path infilepath,                    /* csv file to fit */
      std::vector<std::string> indepVarNames, /* vector of x like values */
      std::string depVarNames,                /* y like variable to fit */
      optimizers::GenericGradientbasedOptimizer
          opt,          /* optimizer (gradient desent/sgd/adam etc... */
      std::string loss, /* l1 or l2 loss */
      bool saveIntermediateProgress /* dump intermediate progress to file to
                                       plot later */
  );

  LinearRegression(fs::path infilepath, bool saveIntermediateProgress);
  LinearRegression(std::vector<double> x, std::vector<double> y,
                   bool saveIntermediateProgress);
  LinearRegression(std::vector<double> x, std::vector<std::vector<double>> y,
                   bool saveIntermediateProgress);

  LinearRegression(std::vector<double> x, std::vector<double> y);
  LinearRegression(std::vector<double> x, std::vector<std::vector<double>> y);

  void fit();
};
};  // namespace models
};  // namespace mznn
#endif  // LINEARREGRESSION_HPP
