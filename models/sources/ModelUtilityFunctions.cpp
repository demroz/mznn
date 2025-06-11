#include <ModelUtilityFunctions.hpp>
#include <regex>
namespace mznn {
namespace models {

namespace fs = std::filesystem;

std::unordered_map<std::string, std::vector<double>> parse_csv_for_model(
    fs::path infile, std::vector<std::string> variable_names) {
  /*
   * parses csv file, returns hashmap with keys being the
   * variable names and values being the vectors of doubles
   *
   * */
  rapidcsv::Document doc(infile, rapidcsv::LabelParams(),
                         rapidcsv::SeparatorParams(),
                         rapidcsv::ConverterParams(),
                         rapidcsv::LineReaderParams(true /* pSkipCommentLines*/,
                                                    '#' /*pCommentPrefix*/));

  std::vector<std::string> column_names = doc.GetColumnNames();
  std::unordered_map<std::string, std::vector<double>> data;

  /* over variable names */
  for (auto xvarname : variable_names) {
    /* throws error if variable name not in csv file */
    if (std::find(column_names.begin(), column_names.end(), xvarname) ==
        column_names.end()) {
      std::string message =
          xvarname + " variable name doesn't exist in csv file.\n.";
      LOG_ERROR(message);
      throw std::domain_error(message);
    }
    /* gets column and places it in hashmap */
    std::vector<double> col;
    col = doc.GetColumn<double>(xvarname);
    data[xvarname] = col;
  }
  return data;
}

/* some loss functions */
void l1_loss(aad::aVector* x, Eigen::VectorX<double>* y, aad::ascalar* loss) {
  aad::aVector err, absolute_error;
  err = *x - *y;
  absolute_error = err.cwiseAbs();
  *loss = absolute_error.sum() / double(err.size());
}

void l2_loss(aad::aVector* x, Eigen::VectorX<double>* y, aad::ascalar* loss) {
  aad::aVector err, absolute_error;
  err = *x - *y;
  absolute_error = err.cwiseAbs2();
  *loss = absolute_error.sum() / double(err.size());
}
std::unordered_map<std::string, double> parse_csv_header_metadata_2D(
    const std::string& filepath) {
  std::unordered_map<std::string, double> metadata;
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open file: " + filepath);
  }

  std::string line;
  std::regex slope_regex(R"(slope:\s*([-+]?[0-9]*\.?[0-9]+))");
  std::regex intercept_regex(R"(intercept:\s*([-+]?[0-9]*\.?[0-9]+))");
  std::regex noise_regex(R"(noise std:\s*([-+]?[0-9]*\.?[0-9]+))");

  while (std::getline(file, line)) {
    // Only process comment lines
    if (line.empty() || line[0] != '#') break;

    std::smatch match;

    if (std::regex_search(line, match, slope_regex)) {
      if (line.find("fit") != std::string::npos)
        metadata["fit_slope"] = std::stod(match[1]);
      else
        metadata["slope"] = std::stod(match[1]);
    } else if (std::regex_search(line, match, intercept_regex)) {
      if (line.find("fit") != std::string::npos)
        metadata["fit_intercept"] = std::stod(match[1]);
      else
        metadata["intercept"] = std::stod(match[1]);
    } else if (std::regex_search(line, match, noise_regex)) {
      metadata["noise_std"] = std::stod(match[1]);
    }
  }

  return metadata;
}

std::unordered_map<std::string, double> parse_csv_header_metadata_5D(
    const std::string& filename) {
  std::unordered_map<std::string, double>
      metadata;                  // This will store our extracted data
  std::ifstream file(filename);  // Open the file specified by filename

  // Check if the file was successfully opened
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return metadata;  // Return an empty map if file opening failed
  }

  std::string line;  // To read each line from the file

  // Regular expressions for matching the metadata lines
  // (.*?) is used to non-greedily capture any characters for the key,
  // accommodating keys with spaces like "normal noise std".
  // We will then filter these keys to only include slopes and intercepts.
  std::regex generated_regex(R"(^# generated with (.*?): ([-]?\d+\.\d+))");
  std::regex fit_regex(R"(^# fit (.*?): ([-]?\d+\.\d+))");

  // Iterate over each line in the file
  while (std::getline(file, line)) {
    // Only process lines that start with '#'
    if (line.rfind('#', 0) == 0) {  // Check if the line starts with '#'
      std::smatch matches;          // To store the results of the regex match

      std::string prefix;
      std::string key_part_candidate;
      double value;
      bool parsed_successfully = false;

      // Try to match with 'generated' pattern
      if (std::regex_search(line, matches, generated_regex)) {
        if (matches.size() ==
            3) {  // Expecting 3 groups: full match, key, value
          prefix = "generated_";
          key_part_candidate =
              matches[1]
                  .str();  // e.g., "slope_x0", "intercept", "normal noise std"
          value = std::stod(matches[2].str());  // Convert string to double
          parsed_successfully = true;
        }
      }
      // Try to match with 'fit' pattern if not matched by 'generated'
      else if (std::regex_search(line, matches, fit_regex)) {
        if (matches.size() == 3) {
          prefix = "fit_";
          key_part_candidate = matches[1].str();
          value = std::stod(matches[2].str());
          parsed_successfully = true;
        }
      }

      // If a valid line was parsed, check if the key is a slope or intercept
      if (parsed_successfully) {
        // Use regex to check if the key_part_candidate is 'slope_xN' or
        // 'intercept'
        std::regex slope_or_intercept_regex(R"(^(slope_x[0-9]|intercept)$)");
        if (std::regex_match(key_part_candidate, slope_or_intercept_regex)) {
          metadata[prefix + key_part_candidate] = value;  // Store with prefix
        }
      }
    }
  }

  file.close();  // Close the file after reading
  return metadata;
}

/*
 * F-statistic CDF
 * */

}  // namespace models
}  // namespace mznn
