#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::setw, std::left, std::right, std::fixed, std::scientific, std::setprecision
#include <sstream> // For std::stringstream
#include <algorithm> // For std::max
#include <type_traits> // For std::is_floating_point, std::enable_if_t

class TableFormatter {
public:
    TableFormatter() : float_precision(2), use_scientific(false) {}

    // Sets the column names for the table
    void setColumnNames(const std::vector<std::string>& names) {
        column_names = names;
        // Initialize column widths with column name lengths
        column_widths.resize(column_names.size());
        for (size_t i = 0; i < column_names.size(); ++i) {
            column_widths[i] = std::max(column_widths[i], static_cast<int>(column_names[i].length()));
        }
    }

    // Adds a row of data to the table using variadic templates.
    // Each argument will be converted to a string.
    template<typename... Args>
    void addRow(Args&&... args) {
        std::vector<std::string> current_row_strings;
        // Process each argument and convert it to a string, then add to the current row
        (current_row_strings.push_back(valueToString(std::forward<Args>(args))), ...);

        if (current_row_strings.size() != column_names.size()) {
            std::cerr << "Error: Row data size (" << current_row_strings.size()
                      << ") does not match column count (" << column_names.size() << ")." << std::endl;
            return;
        }
        data_rows.push_back(current_row_strings);

        // Update column widths based on the new row's content
        for (size_t i = 0; i < current_row_strings.size(); ++i) {
            column_widths[i] = std::max(column_widths[i], static_cast<int>(current_row_strings[i].length()));
        }
    }

    // Sets the precision for floating-point numbers
    void setFloatPrecision(int precision) {
        if (precision >= 0) {
            float_precision = precision;
        } else {
            std::cerr << "Warning: Float precision cannot be negative. Setting to 0." << std::endl;
            float_precision = 0;
        }
    }

    // Sets whether to use scientific notation for floating-point numbers
    void setFloatScientific(bool scientific) {
        use_scientific = scientific;
    }

    // Prints the formatted table to the console
    void printTable() const {
        if (column_names.empty()) {
            std::cout << "No columns defined." << std::endl;
            return;
        }

        // Print header separator
        printHorizontalLine();

        // Print column names (centered)
        for (size_t i = 0; i < column_names.size(); ++i) {
            std::cout << "|";
            const std::string& name = column_names[i];
            int width = column_widths[i];
            int padding_left = (width - name.length()) / 2;
            int padding_right = width - name.length() - padding_left;
            std::cout << std::string(padding_left, ' ') << name << std::string(padding_right, ' ');
        }
        std::cout << "|" << std::endl;

        // Print header-data separator
        printHorizontalLine();

        // Print data rows
        for (const auto& row : data_rows) {
            for (size_t i = 0; i < row.size(); ++i) {
                std::cout << "|";
                const std::string& cell_str = row[i]; // Already converted to string
                // Data is left-aligned
                std::cout << std::left << std::setw(column_widths[i]) << cell_str;
            }
            std::cout << "|" << std::endl;
        }

        // Print footer separator
        printHorizontalLine();
    }

private:
    std::vector<std::string> column_names;
    // Data rows now store strings directly
    std::vector<std::vector<std::string>> data_rows;
    std::vector<int> column_widths; // Stores the calculated max width for each column
    int float_precision;
    bool use_scientific;

    // Helper to convert any value to string using if constexpr for conditional formatting.
    template<typename T>
    std::string valueToString(const T& val) const {
        std::stringstream ss;

        // Use if constexpr to apply floating-point formatting only if T is a floating-point type
        if constexpr (std::is_floating_point<T>::value) {
            ss << std::fixed << std::setprecision(float_precision);
            if (use_scientific) {
                ss << std::scientific;
            }
        }
        ss << val;
        return ss.str();
    }

    // Helper to print a horizontal line for table separators
    void printHorizontalLine() const {
        std::cout << "+";
        for (size_t i = 0; i < column_names.size(); ++i) {
            std::cout << std::string(column_widths[i], '-');
            std::cout << "+";
        }
        std::cout << std::endl;
    }
};

int main() {
    TableFormatter table;

    // Example 1: Basic table with default float formatting
    std::cout << "--- Example 1: Basic Table ---" << std::endl;
    table.setColumnNames({"Name", "Age", "Height (m)", "Status"});
    table.addRow("Alice", 30, 1.75, "Active");
    table.addRow("Bob Smith", 24, 1.825, "Inactive");
    table.addRow("Charlie", 45, 1.68, "Admin");
    table.printTable();
    std::cout << std::endl;

    // Example 2: Table with custom float precision
    TableFormatter table2;
    std::cout << "--- Example 2: Custom Float Precision (3 decimals) ---" << std::endl;
    table2.setColumnNames({"Product", "Price", "Weight (kg)"});
    table2.setFloatPrecision(3); // Set precision to 3 decimal places
    table2.addRow("Laptop", 1200.55, 2.12345);
    table2.addRow("Mouse", 25.99, 0.15);
    table2.addRow("Keyboard", 75.0, 0.789);
    table2.printTable();
    std::cout << std::endl;

    // Example 3: Table with scientific notation for floats
    TableFormatter table3;
    std::cout << "--- Example 3: Scientific Notation ---" << std::endl;
    table3.setColumnNames({"Experiment", "Value A", "Value B"});
    table3.setFloatPrecision(4); // Set precision for scientific notation
    table3.setFloatScientific(true); // Enable scientific notation
    table3.addRow("Exp1", 0.000012345, 9876543.21);
    table3.addRow("Exp2", 1.23, 0.000987);
    table3.printTable();
    std::cout << std::endl;

    // Example 4: Mixed data types and longer strings
    TableFormatter table4;
    std::cout << "--- Example 4: Mixed Data Types and Longer Strings ---" << std::endl;
    table4.setColumnNames({"Item ID", "Description of Item", "Quantity", "Unit Cost", "Total Value"});
    table4.setFloatPrecision(2);
    table4.addRow(101, "A very long description for a widget", 5, 12.345, 61.725);
    table4.addRow(203, "Another item", 100, 0.50, 50.0);
    table4.addRow(305, "Short item", 2, 99.99, 199.98);
    table4.printTable();
    std::cout << std::endl;

    return 0;
}
