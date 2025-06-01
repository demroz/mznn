#include "linearRegression.hpp"

int main() {
  /*
  Eigen::Matrix<aad::ascalar, 2, 2> A;
  A(0, 0) = 1.0;
  A(0, 1) = 0.0;
  A(1, 0) = 0.0;
  A(1, 1) = 1.0;

  Eigen::VectorX<aad::ascalar> x;

  x.resize(2);
  x(0) = 1.0;
  x(1) = 2.0;

  Eigen::VectorX<aad::ascalar> b(2);
  b = A * x;
  std::cout << b << std::endl;*/

  std::vector<std::string> varnames;
  varnames.push_back("x0");
  varnames.push_back("x1");
  mznn::LinearRegression lro(
      "/home/mzhelyez/Documents/code/mznn/linear-regression/../datasets/"
      "linreg_dataset_3D.csv",
      varnames, "y", true);

  lro.fit();
  return 0;
}
