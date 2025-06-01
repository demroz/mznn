#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include <rapidcsv.h>

#include <Eigen/Eigen>
#include <addutils.hpp>
#include <algorithm>
#include <autodiff.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
namespace mznn {
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

  std::vector<double> _lossVector;
  std::vector<aad::ascalar*> _coeffs;

  std::vector<std::string> _columnNames;
  size_t _numIndepVars;
  size_t _numrows;
  bool _dumpToFile;
  bool _saveIntermediateresults;

  Eigen::MatrixX<double> _A;
  Eigen::VectorX<double> _b;
  aad::aVector _x;
  double _learning_rate = 1e-4;
  void _loadFile(fs::path, std::vector<std::string>, std::string);
  void _initRandomLowHigh(double low, double high);
  void _initWithGuess(std::vector<double> guess);
  void _setup();
  void _l1loss(aad::aVector* x, Eigen::VectorX<double>* y, aad::ascalar* loss);
  void _l2loss(aad::aVector* x, Eigen::VectorX<double>* y, aad::ascalar* loss);

 public:
  LinearRegression(fs::path infilepath, std::vector<std::string> indepVarNames,
                   std::string depVarNames, bool saveIntermediateProgress);
  LinearRegression(fs::path infilepath, bool saveIntermediateProgress);
  LinearRegression(std::vector<double> x, std::vector<double> y,
                   bool saveIntermediateProgress);
  LinearRegression(std::vector<double> x, std::vector<std::vector<double>> y,
                   bool saveIntermediateProgress);
  LinearRegression(std::vector<double> x, std::vector<double> y);
  LinearRegression(std::vector<double> x, std::vector<std::vector<double>> y);
  ~LinearRegression() {};

  void fit();

};
};  // namespace mznn
#endif  // LINEARREGRESSION_HPP
