#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include <rapidcsv.h>

#include <Eigen/Eigen>
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
  std::vector<std::vector<double>> _xdata;
  std::vector<double> _ydata;
  std::vector<std::string> _columnNames;
  size_t _numIndepVars;
  size_t _numrows;

  void load_from_file(fs::path);

 public:
  LinearRegression(fs::path infilepath, fs::path outfilepath,
                   std::vector<std::string> indepVarNames,
                   std::string depVarNames);

  LinearRegression(fs::path infilepath, fs::path outfilepath);
  LinearRegression(std::vector<double> x, std::vector<double> y);
  LinearRegression(std::vector<double> x, std::vector<std::vector<double>> y);

  ~LinearRegression() {};
};
};  // namespace mznn
#endif  // LINEARREGRESSION_HPP
