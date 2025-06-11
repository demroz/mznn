#ifndef PARSE_CSV_HPP
#define PARSE_CSV_HPP

#include <rapidcsv.h>

#include <filesystem>
#include <log.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <autodiff.hpp>
namespace mznn {
namespace models {

namespace fs = std::filesystem;

class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error("Function not yet implemented") { };
    NotImplemented(std::string what) : std::logic_error(what) {};
};

std::unordered_map<std::string, std::vector<double>> parse_csv_for_model(
    fs::path infile, std::vector<std::string> variable_names);

void l1_loss(aad::aVector*, Eigen::VectorX<double>*, aad::ascalar* loss);
void l2_loss(aad::aVector*, Eigen::VectorX<double>*, aad::ascalar* loss);
std::unordered_map<std::string, double> parse_csv_header_metadata_2D(const std::string& filepath);
std::unordered_map<std::string, double> parse_csv_header_metadata_5D(
    const std::string& filepath);
}// namespace models
}  // namespace mznn
#endif  // PARSE_CSV_HPP
