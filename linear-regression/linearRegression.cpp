#include "linearRegression.hpp"

#include <log.hpp>
namespace mznn {
LinearRegression::LinearRegression(fs::path infile, fs::path outfile,
                                   std::vector<std::string> indepVarNames,
                                   std::string depVarname) {
  /*
   * @brief	Constructor
   * 		reads infile. sets dependent/independent variables
   * 		throws exceptions if file doesn't exist or variables are named
   * 		incorrectly
   *
   * @param	filesystem::path infile
   * 		input data file
   *
   * @param	filesystem::path outfile
   * 		path where results get saved
   *
   * @param	vector<string> indepVarNames
   * 		list of independent variable names (x's)
   *
   * @param	string
   * 		dependent variable name (y)
   */
  _infilePath = infile;
  _outfilePath = outfile;

  try {
    rapidcsv::Document doc(
        infile, rapidcsv::LabelParams(), rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(),
        rapidcsv::LineReaderParams(true /* pSkipCommentLines */,
                                   '#' /* pCommentPrefix */));

    _columnNames = doc.GetColumnNames();
    for (auto xvarname : indepVarNames) {
      std::cout << xvarname << std::endl;
      if (std::find(_columnNames.begin(), _columnNames.end(), xvarname) ==
          _columnNames.end()) {
        std::string message = xvarname + " variable name does not exist\n";
        throw std::domain_error(message);
      }
      std::vector<double> col;
      col = doc.GetColumn<double>(xvarname);
      _xdata.push_back(col);
    }
    _ydata = doc.GetColumn<double>(depVarname);
    _numrows = _ydata.size();

  } catch (const std::exception& ex) {
    LOG_ERROR(ex.what());
    LOG_ERROR("terminating program");
    return;
  }
}
void LinearRegression::load_from_file(fs::path filepath) {
  rapidcsv::Document doc(
      filepath, rapidcsv::LabelParams(), rapidcsv::SeparatorParams(),
      rapidcsv::ConverterParams(),
      rapidcsv::LineReaderParams(true /* pSkipCommentLines */,
                                 '#' /* pCommentPrefix */));
  _columnNames = doc.GetColumnNames();
  for (auto colname : _columnNames) {
    std::cout << colname << std::endl;
  }
}

}  // namespace mznn
