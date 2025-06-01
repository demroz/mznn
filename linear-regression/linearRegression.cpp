#include "linearRegression.hpp"

#include <log.hpp>

#include "../optimizers/GradientDescentOptimizer.hpp"
namespace mznn {
LinearRegression::LinearRegression(fs::path infile,
                                   std::vector<std::string> indepVarNames,
                                   std::string depVarname,
                                   bool saveIntermediateProgress) {
  /*
   * @brief	Constructor
   * 		reads infile. sets dependent/independent variables
   * 		throws exceptions if file doesn't exist or variables are named
   * 		incorrectly
   *
   * @param	filesystem::path infile
   * 		input data file
   *
   * @param	vector<string> indepVarNames
   * 		list of independent variable names (x's)
   *
   * @param	string
   * 		dependent variable name (y)
   */
  _infilePath = infile;

  try {
    _loadFile(infile, indepVarNames, depVarname);
  } catch (const std::exception& ex) {
    LOG_ERROR(ex.what());
    LOG_ERROR("terminating program");
    return;
  }
}

void LinearRegression::_initRandomLowHigh(double low, double high) {
    /*
     * initializes fit with random numbers
     * low/high are bounds for rng
     * */
  _x.resize(_numIndepVars);
  for (size_t i = 0; i < _numIndepVars; i++) {
    double x;
    x = random(low, high);
    _x(i) = x;
    _coeffs.push_back(&_x[i]);
  }
}

void LinearRegression::_initWithGuess(std::vector<double> guess) {
    /*
     * initializes with manual guess
     * */
  _x.resize(_numIndepVars);
  for (size_t i = 0; i < _numIndepVars; i++) {
    _x(i) = guess[i];
    _coeffs.push_back(&_x[i]);
  }
}


void LinearRegression::_l2loss(aad::aVector* x, Eigen::VectorX<double>* y,
                               aad::ascalar* loss) {
   /*
    * mean square error
    * */

  aad::aVector err, abserr;
  err = *x - *y;
  abserr = err.cwiseAbs2();
  *loss = abserr.sum() / double(_numrows);
}

void LinearRegression::_l1loss(aad::aVector* x, Eigen::VectorX<double>* y,
                               aad::ascalar* loss){
    /*
     * abs error
     * */
    aad::aVector err, abserr;
    err = *x - *y;
    abserr = err.cwiseAbs();
    *loss = abserr.sum() / double(_numrows);

}

void LinearRegression::fit() {
  _initRandomLowHigh(-1, 1);
  aad::ascalar::tape->mark();
  aad::ascalar loss;
  aad::aVector Ax;

  optimizers::GradientDescent opt(_coeffs, _learning_rate);
  for (size_t i = 0; i < 10000; i++) {
    aad::ascalar::tape->rewindToMark();
    opt.zero_grad();
    Ax = _A * _x;
    _l2loss(&Ax, &_b, &loss);
    loss.propagateToStart();
    std::cout << loss.item() << std::endl;
    opt.step();
  }
  std::cout << _x << std::endl;
}

void LinearRegression::_loadFile(fs::path infile,
                                 std::vector<std::string> indepVarNames,
                                 std::string depVarname) {
  rapidcsv::Document doc(
      infile, rapidcsv::LabelParams(), rapidcsv::SeparatorParams(),
      rapidcsv::ConverterParams(),
      rapidcsv::LineReaderParams(true /* pSkipCommentLines */,
                                 '#' /* pCommentPrefix */));

  _columnNames = doc.GetColumnNames();
  std::vector<std::vector<double>> xdata;
  xdata.push_back(std::vector<double>());
  std::vector<double> ydata;

  for (auto xvarname : indepVarNames) {
    std::cout << xvarname << std::endl;
    if (std::find(_columnNames.begin(), _columnNames.end(), xvarname) ==
        _columnNames.end()) {
      std::string message = xvarname + " variable name does not exist\n";
      throw std::domain_error(message);
    }
    std::vector<double> col;
    col = doc.GetColumn<double>(xvarname);
    xdata.push_back(col);
  }
  ydata = doc.GetColumn<double>(depVarname);
  _numrows = ydata.size();
  _numIndepVars = xdata.size();
  for (size_t i = 0; i < _numrows; i++) {
    xdata[0].push_back(1.0);
  }
  _b.resize(_numrows);
  _A.resize(_numrows, _numIndepVars);
  for (size_t i = 0; i < _numrows; i++) {
    _b(i) = ydata[i];
    for (size_t j = 0; j < _numIndepVars; j++) {
      _A(i, j) = xdata[j][i];
    }
  }
}

}  // namespace mznn
