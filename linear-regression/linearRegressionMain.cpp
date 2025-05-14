#include "linearRegression.hpp"

int main() {
  std::vector<std::string> varnames;
  varnames.push_back("x");
  mznn::LinearRegression lro(
      "/home/mzhelyez/Documents/code/mznn/linear-regression/../datasets/"
      "linreg_dataset_2D.csv",
      "outfile.csv", varnames, "yq");
  return 0;
}
