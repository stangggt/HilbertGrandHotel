#include "ConsoleUtils.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

namespace ConsoleUtils {

    void clearScreen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void printDivider(int width, char ch) {
        std::cout << Color::DIM;
        for (int i = 0; i < width; ++i) {
            std::cout << ch;
        }
        std::cout << Color::RESET << "\n";
    }

    void printHeader(const std::string& title, const std::string& subtitle) {
        std::cout << "\n";
        printDivider(78, '=');
        std::cout << Color::BOLD_CYAN << "  ✦ " << title << Color::RESET;
        if (!subtitle.empty()) {
            std::cout << Color::DIM << "  |  " << subtitle << Color::RESET;
        }
        std::cout << "\n";
        printDivider(78, '=');
    }

    void printBox(const std::string& title, const std::vector<std::string>& lines, int width) {
        std::cout << Color::CYAN << "┌─ " << Color::BOLD_WHITE << title << " "
                  << Color::CYAN;
        int titleLen = static_cast<int>(title.length()) + 4;
        for (int i = titleLen; i < width; ++i) std::cout << "─";
        std::cout << "┐\n" << Color::RESET;

        for (const auto& line : lines) {
            std::cout << Color::CYAN << "│ " << Color::RESET;
            std::cout << std::left << std::setw(width - 4) << line;
            std::cout << Color::CYAN << " │\n" << Color::RESET;
        }

        std::cout << Color::CYAN << "└";
        for (int i = 0; i < width - 2; ++i) std::cout << "─";
        std::cout << "┘\n" << Color::RESET;
    }

    void printTable(const std::vector<std::string>& headers,
                    const std::vector<int>& widths,
                    const std::vector<std::vector<std::string>>& rows) {
        if (headers.size() != widths.size()) return;

        // Top Border
        std::cout << Color::DIM << "┌";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int w = 0; w < widths[i] + 2; ++w) std::cout << "─";
            if (i + 1 < widths.size()) std::cout << "┬";
        }
        std::cout << "┐\n" << Color::RESET;

        // Header Row
        std::cout << Color::DIM << "│" << Color::RESET;
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << " " << Color::BOLD_YELLOW
                      << std::left << std::setw(widths[i]) << headers[i]
                      << Color::RESET << Color::DIM << " │" << Color::RESET;
        }
        std::cout << "\n";

        // Header Separator
        std::cout << Color::DIM << "├";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int w = 0; w < widths[i] + 2; ++w) std::cout << "─";
            if (i + 1 < widths.size()) std::cout << "┼";
        }
        std::cout << "┤\n" << Color::RESET;

        // Data Rows
        for (const auto& row : rows) {
            std::cout << Color::DIM << "│" << Color::RESET;
            for (size_t i = 0; i < widths.size(); ++i) {
                std::string cell = (i < row.size()) ? row[i] : "";
                std::cout << " " << std::left << std::setw(widths[i]) << cell
                          << Color::DIM << " │" << Color::RESET;
            }
            std::cout << "\n";
        }

        // Bottom Border
        std::cout << Color::DIM << "└";
        for (size_t i = 0; i < widths.size(); ++i) {
            for (int w = 0; w < widths[i] + 2; ++w) std::cout << "─";
            if (i + 1 < widths.size()) std::cout << "┴";
        }
        std::cout << "┘\n" << Color::RESET;
    }

    std::string readLine(const std::string& prompt) {
        std::cout << Color::BOLD_CYAN << prompt << Color::RESET;
        std::string input;
        std::getline(std::cin, input);
        // Trim leading and trailing spaces
        size_t start = input.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        size_t end = input.find_last_not_of(" \t\r\n");
        return input.substr(start, end - start + 1);
    }

    int readInt(const std::string& prompt, int minVal, int maxVal) {
        while (true) {
            std::string s = readLine(prompt);
            try {
                int val = std::stoi(s);
                if (val >= minVal && val <= maxVal) {
                    return val;
                }
                std::cout << Color::BOLD_RED << "  [!] Value must be between "
                          << minVal << " and " << maxVal << ". Please try again.\n" << Color::RESET;
            } catch (...) {
                std::cout << Color::BOLD_RED << "  [!] Invalid number. Please enter an integer.\n" << Color::RESET;
            }
        }
    }

    double readDouble(const std::string& prompt, double minVal, double maxVal) {
        while (true) {
            std::string s = readLine(prompt);
            try {
                double val = std::stod(s);
                if (val >= minVal && val <= maxVal) {
                    return val;
                }
                std::cout << Color::BOLD_RED << "  [!] Value must be between "
                          << minVal << " and " << maxVal << ". Please try again.\n" << Color::RESET;
            } catch (...) {
                std::cout << Color::BOLD_RED << "  [!] Invalid number. Please enter a valid decimal number.\n" << Color::RESET;
            }
        }
    }

    bool readBool(const std::string& prompt) {
        while (true) {
            std::string s = readLine(prompt + " (y/n): ");
            if (s == "y" || s == "Y" || s == "yes" || s == "YES") return true;
            if (s == "n" || s == "N" || s == "no" || s == "NO") return false;
            std::cout << Color::BOLD_RED << "  [!] Please enter 'y' or 'n'.\n" << Color::RESET;
        }
    }

    void pause(const std::string& message) {
        std::cout << "\n" << Color::DIM << message << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

} // namespace ConsoleUtils
