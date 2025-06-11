#ifndef PRETTYTABLE_HPP
#define PRETTYTABLE_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class PrettyTable {
 private:
  /* separator characters
   * Example:
   *
   * +----------+----------+----------+
   * |Experiment| Value A  | Value B  |
   * +----------+----------+----------+
   * |Exp1      |1.2345e-05|9.8765e+06|
   * |Exp2      |1.2300e+00|9.8700e-04|
   * +----------+----------+----------+
   */

  char _hchar = '-';
  char _vchar = '|';
  char _cchar = '+';

  std::vector<std::string> _column_names;
  std::vector<std::vector<std::string>> _data_rows;
  std::vector<int> _column_widths;

  unsigned int _float_precision = 3;
  bool _use_scientific = false;

  template <typename T>
  std::string _to_string(const T& val) const {
    /*
     * converts templated value T to string
     * */
    std::stringstream ss;
    if constexpr (std::is_floating_point<T>::value) {
      ss << std::fixed << std::setprecision(_float_precision);
      if (_use_scientific) {
        ss << std::scientific;
      }
    }
    ss << val;
    return ss.str();
  }

  void _print_ln() const {
    std::cout << _cchar;
    for (size_t i = 0; i < _column_names.size(); ++i) {
      std::cout << std::string(_column_widths[i], _hchar);
      std::cout << _cchar;
    }
    std::cout << std::endl;
  }

 public:
  PrettyTable() {};
  PrettyTable(std::vector<std::string>& column_names) {
    set_column_names(column_names);
  };

  /* configuration setters */
  void set_float_precision(unsigned int float_precision) {
    _float_precision = float_precision;
  };
  void set_use_scientific(bool flag) { _use_scientific = flag; }

  void set_column_names(const std::vector<std::string>& names) {
    _column_names = names;
    _column_widths.resize(_column_names.size());
    for (size_t i = 0; i < _column_names.size(); ++i) {
      _column_widths[i] = std::max(_column_widths[i],
                                   static_cast<int>(_column_names[i].length()));
    }
  }

  template <typename... Args>
  void add_row(Args&&... args) {
    std::vector<std::string> current_row_strings;
    (current_row_strings.push_back(_to_string(std::forward<Args>(args))), ...);

    if (current_row_strings.size() != _column_names.size()) {
      std::cerr << "Error: Row data size (" << current_row_strings.size()
                << ") does not match column count (" << _column_names.size()
                << ")." << std::endl;
      return;
    }
    _data_rows.push_back(current_row_strings);

    for (size_t i = 0; i < current_row_strings.size(); ++i) {
      _column_widths[i] = std::max(
          _column_widths[i], static_cast<int>(current_row_strings[i].length()));
    }
  }

  void print() const {
    if (_column_names.empty()) {
        return;
    }

    _print_ln();

    for (size_t i = 0; i < _column_names.size(); ++i) {
        std::cout << _vchar;
        const std::string& name = _column_names[i];
        int width = _column_widths[i];
        int padding_left = (width - name.length()) / 2;
        int padding_right = width - name.length() - padding_left;
        std::cout << std::string(padding_left, ' ') << name << std::string(padding_right, ' ');
    }
    std::cout << _hchar << std::endl;

    _print_ln();

    for (const auto& row : _data_rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << _vchar;
            const std::string& cell_str = row[i];
            std::cout << std::left << std::setw(_column_widths[i]) << cell_str;
        }
        std::cout << _vchar << "\n";
    }
    std::cout<<std::endl;
    _print_ln();
}
};

#endif  // PRETTYPRING_HPP
