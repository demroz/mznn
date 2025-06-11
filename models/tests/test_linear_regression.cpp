#include <gtest/gtest.h>

#include <LinearRegression.hpp>
#include <ModelUtilityFunctions.hpp>

namespace mznn {
namespace models {

class LinearRegressionTest : public ::testing::Test {
 protected:
  mznn::models::LinearRegression* lr;
  std::string csv_filename =
      std::string(CSV_DATA_PATH) + "/linreg_dataset_2D.csv";
  std::vector<std::string> variable_names;
  std::unordered_map<std::string, std::vector<double>> csv_dataset;
  std::vector<std::vector<double>> independent_variable;
  std::vector<double> dependent_variable;

  void SetUp() override {
    variable_names.push_back("x");
    variable_names.push_back("y");
    csv_dataset =
        mznn::models::parse_csv_for_model(csv_filename, variable_names);

    independent_variable.push_back(csv_dataset["x"]);
    dependent_variable = csv_dataset["y"];

    mznn::models::ModelConfig config;
    lr = new mznn::models::LinearRegression(independent_variable,
                                            dependent_variable, config);
  }

  void TearDown() override {
    // optional teardown
  }
  void reset_config(mznn::models::ModelConfig config) {
    if (lr != nullptr) {
      delete lr;
    }
    lr = new mznn::models::LinearRegression(independent_variable,
                                            dependent_variable, config);
  }

  void reset_to_5D_dataset(mznn::models::ModelConfig config) {
    csv_filename = std::string(CSV_DATA_PATH) + "/linreg_dataset_5D.csv";
    variable_names.clear();
    variable_names.push_back("x0");
    variable_names.push_back("x1");
    variable_names.push_back("x2");
    variable_names.push_back("x3");
    variable_names.push_back("y");
    csv_dataset =
        mznn::models::parse_csv_for_model(csv_filename, variable_names);
    independent_variable.clear();
    independent_variable.push_back(csv_dataset["x0"]);
    independent_variable.push_back(csv_dataset["x1"]);
    independent_variable.push_back(csv_dataset["x2"]);
    independent_variable.push_back(csv_dataset["x3"]);

    dependent_variable = csv_dataset["y"];
    if (lr != nullptr) {
      delete lr;
    }
    lr = new mznn::models::LinearRegression(independent_variable,
                                            dependent_variable, config);
  }
  /* getters to test private stuff */
  std::string get_outfile_path() { return lr->_config.outFilePath; };
  bool get_save_intermediate_results() {
    return lr->_config.saveIntermediateResults;
  };
  double get_learning_rate() { return lr->_config.LEARNING_RATE; };
  size_t get_max_iter() { return lr->_config.MAXITER; }

  Eigen::MatrixX<double> get_matrix() { return lr->_A; }
  Eigen::VectorX<double> get_b() { return lr->_b; };
  aad::aVector get_x() { return lr->_x; };
};
TEST_F(LinearRegressionTest, constructor) {
  /* model config initialization */
  ASSERT_EQ(get_outfile_path(), "");
  ASSERT_FALSE(get_save_intermediate_results());
  ASSERT_EQ(get_learning_rate(), 1e-2);
  ASSERT_EQ(get_max_iter(), 1000000);
}

TEST_F(LinearRegressionTest, test_initializers) {
  /* initialize linear system */
  Eigen::MatrixX<double> A = get_matrix();
  Eigen::VectorX<double> b = get_b();
  aad::aVector x = get_x();
  ASSERT_EQ(A.rows(), csv_dataset["x"].size());
  ASSERT_EQ(b.rows(), csv_dataset["x"].size());
  ASSERT_EQ(A.cols(), 2);

  for (size_t i = 0; i < csv_dataset["x"].size(); ++i) {
    ASSERT_EQ(A(i, 0), 1.0);
    EXPECT_NEAR(A(i, 1), csv_dataset["x"][i], 1e-6);
    EXPECT_NEAR(b(i), csv_dataset["y"][i], 1e-6);
  }
  /* no initial guess */
  EXPECT_NEAR(x(0).item(), 0.0, 1e-6);
  EXPECT_NEAR(x(1).item(), 0.0, 1e-6);

  /* initial guess provided */
  mznn::models::ModelConfig config_with_initial_guess;

  std::vector<double> initial_guess{1.0, 3.14};
  config_with_initial_guess.initial_guess = initial_guess;
  reset_config(config_with_initial_guess);
  x = get_x();
  EXPECT_NEAR(x(0).item(), 1.00, 1e-6);
  EXPECT_NEAR(x(1).item(), 3.14, 1e-6);

  /* loss function l2 */
  aad::aVector x1;
  Eigen::VectorX<double> x2;
  aad::ascalar test_loss;
  x1.resize(2);
  x1(0) = 3.0;
  x1(1) = 4.0;

  x2.resize(2);
  x2.setZero();

  lr->call_loss(&x1, &x2, &test_loss);
  EXPECT_NEAR(test_loss.item(), 12.5, 1e-6);

  /* reset, test l1 loss */
  mznn::models::ModelConfig config_with_l1_loss;
  config_with_l1_loss.loss_function = "l1";
  reset_config(config_with_l1_loss);

  lr->call_loss(&x1, &x2, &test_loss);
  EXPECT_NEAR(test_loss.item(), 3.5, 1e-6);

  /* unimplemented error */
  mznn::models::ModelConfig config_with_junk_loss;
  config_with_junk_loss.loss_function = "junk";
  EXPECT_THROW(
      {
        try {
          reset_config(config_with_junk_loss);
        } catch (const NotImplemented& e) {
          EXPECT_STREQ(
              "loss funciton not implemented. only l1 and l2 loss is available "
              "for linear regression models",
              e.what());
          throw;
        }
      },
      NotImplemented);
}

TEST_F(LinearRegressionTest, convergence2) {
  mznn::models::ModelConfig config;
  config.LEARNING_RATE = 1e-3;
  config.CONVERENCE_TOLERANCE = 1e-2;

  std::unordered_map<std::string, double> metadata;
  csv_filename = std::string(CSV_DATA_PATH) + "/linreg_dataset_5D.csv";
  metadata = parse_csv_header_metadata_5D(csv_filename);

  config.initial_guess.push_back(metadata["fit_intercept"]);
  config.initial_guess.push_back(metadata["fit_slope_x0"]);
  config.initial_guess.push_back(metadata["fit_slope_x1"]);
  config.initial_guess.push_back(metadata["fit_slope_x2"]);
  config.initial_guess.push_back(metadata["fit_slope_x3"]);
  reset_to_5D_dataset(config);

  lr->fit();
  auto x = get_x();
  EXPECT_NEAR(x(0).item(), metadata["fit_intercept"], 1e-2);
  EXPECT_NEAR(x(1).item(), metadata["fit_slope_x0"], 1e-2);
  EXPECT_NEAR(x(2).item(), metadata["fit_slope_x1"], 1e-2);
  EXPECT_NEAR(x(3).item(), metadata["fit_slope_x2"], 1e-2);
  EXPECT_NEAR(x(4).item(), metadata["fit_slope_x3"], 1e-2);
}
/*
TEST_F(LinearRegressionTest, convergence1) {
  mznn::models::ModelConfig config;
  config.LEARNING_RATE = 1e-3;
  config.CONVERENCE_TOLERANCE = 1e-2;

  lr->fit();
  auto x = get_x();
}*/
}  // namespace models
}  // namespace mznn
