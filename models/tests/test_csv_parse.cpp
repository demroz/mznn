#include <gtest/gtest.h>

#include <ModelUtilityFunctions.hpp>
TEST(csv_parsing, parse_nd_file) {
  /* no checks performed here
   * this only fails if file doesn't get parsed properly
   * */
  std::string csvfilename =
      std::string(CSV_DATA_PATH) + "/linreg_dataset_5D.csv";
  std::unordered_map<std::string, std::vector<double>> parsed_dataset;
  std::vector<std::string> variable_names;
  variable_names.push_back("x0");
  variable_names.push_back("x1");
  variable_names.push_back("x2");
  variable_names.push_back("x3");
  variable_names.push_back("y");

  parsed_dataset =
      mznn::models::parse_csv_for_model(csvfilename, variable_names);
}
